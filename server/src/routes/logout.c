/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"
#include "json/json.h"
#include "server_utils.h"

response_t logout_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *)data;
    json_object_t *json = (json_object_t *) json_parse(request->body);
    char *user_uuid = NULL;
    roundtable_client_t *client = NULL;

    if (strcmp(request->route.method, "POST") != 0)
        return create_error(405, "Method not allowed", "Only POST");
    if (!json || !json_object_get(json, "user_uuid"))
        return create_error(400, "Invalid body", "Missing user_uuid");
    user_uuid = ((json_string_t *) json_object_get(json,
    "user_uuid"))->value;
    client = roundtable_server_get_client_by_uuid(server,
    *uuid_from_string(user_uuid));
    if (client == NULL)
        return create_error(404, "Client not found", "Client not found");
    if (client->status == OFFLINE)
        return create_error(401, "Unauthorized", "Client already offline");
    client->status = OFFLINE;
    return create_success(204, "");
}
