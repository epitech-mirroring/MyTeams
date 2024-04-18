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
#include "network/dto.h"

static response_t create_user_response(json_object_t *req_body,
    json_object_t *rep_body, roundtable_client_t *client)
{
    response_t response = {0};
    char *response_body_str = NULL;

    json_object_add(rep_body, (json_t *) json_string_create("uuid",
    uuid_to_string(client->uuid)));
    json_object_add(rep_body, (json_t *) json_string_create("name",
    client->username));
    json_object_add(rep_body, (json_t *) json_string_create("status",
    client->status == ONLINE ? "online" : "offline"));
    response_body_str = json_serialize((json_t *) rep_body);
    response.status = 200;
    response.status_message = strdup("OK");
    response.body = strdup(response_body_str);
    response_add_header(&response, "Content-Type", "application/json");
    destroy(response_body_str, (json_t *) req_body, (json_t *) rep_body);
    return response;
}

static roundtable_client_t *get_client(roundtable_server_t *server,
    char *uuid_json_user_info, json_object_t *req_body)
{
    roundtable_client_t *client = NULL;

    if (!uuid_json_user_info)
        uuid_json_user_info = ((json_string_t *) json_object_get(req_body,
        "user_uuid"))->value;
    client = roundtable_server_get_client_by_uuid(server,
        *uuid_from_string(uuid_json_user_info));
    return client;
}

response_t user_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    json_object_t *req_body = (json_object_t *) json_parse(request->body);
    roundtable_client_t *client = NULL;
    json_object_t *rep_body = json_object_create(NULL);

    if (strcmp(request->route.method, "GET") != 0)
        return create_error(405, "Method not allowed", "Only GET");
    if (!req_body || !json_object_get(req_body, "user_uuid"))
        return create_error(400, "Bad JSON", "Missing user_uuid");
    client = get_client(server, request_get_param(request, "user_uuid"),
        req_body);
    if (!client)
        return create_error(404, "Client not found", "No client for"
            " this uuid");
    return create_user_response(req_body, rep_body, client);
}
