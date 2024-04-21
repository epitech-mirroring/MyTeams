/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"
#include "server_utils.h"
#include "network/dto.h"

static void should_set_status_offline(roundtable_server_t *server,
    roundtable_client_instance_t *instance)
{
    roundtable_client_t *client = instance->client;
    size_t instance_count = get_instance_count(server, client);

    if (instance_count == 1)
        return;
    client->status = OFFLINE;
    server_event_user_logged_out(uuid_to_string(client->uuid));
    roundtable_event_logged_out(server, client);
    roundtable_client_instance_remove(server, instance);
}

response_t logout_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *)data;
    roundtable_client_instance_t *instance = NULL;
    roundtable_client_t *client = NULL;

    if (strcmp(request->route.method, "POST") != 0)
        return create_error(405, "Method not allowed", "Only POST");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    instance = get_instance_from_header(server, request);
    if (instance == NULL)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    client = instance->client;
    if (client->status == OFFLINE)
        return create_error(409, "Conflict", "Client already offline");
    should_set_status_offline(server, instance);
    return create_success(200, client->status == OFFLINE ?
        "Has logged out" : "Still logged in");
}
