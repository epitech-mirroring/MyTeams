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
        return create_error(405, "Method Not Allowed", "Method not allowed",
        "Method not allowed");
    if (!json || !json_object_get(json, "user_uuid"))
        return create_error(400, "Bad Request", "Bad JSON", "Invalid JSON");
    user_uuid = ((json_string_t *) json_object_get(json,
    "user_uuid"))->value;
    client = roundtable_server_get_client_by_uuid(server,
    *uuid_from_string(user_uuid));
    if (!client)
        return create_error(404, "Not Found", "Client not found",
        "Client not found");
    client->status = OFFLINE;
    return create_success(200, "OK");
}
