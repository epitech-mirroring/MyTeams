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

response_t logout_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *)data;
    roundtable_client_t *client = NULL;

    if (strcmp(request->route.method, "POST") != 0)
        return create_error(405, "Method not allowed", "Only POST");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    client = get_client_from_header(server, request);
    if (client == NULL)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    if (client->status == OFFLINE)
        return create_error(409, "Conflict", "Client already offline");
    client->status = OFFLINE;
    server_event_user_logged_out(uuid_to_string(client->uuid));
    roundtable_event_logged_out(server, client);
    return create_success(204, "");
}
