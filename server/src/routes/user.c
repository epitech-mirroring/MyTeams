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


static roundtable_client_t *get_client(request_t *request,
    json_object_t *body, roundtable_server_t *srv)
{
    roundtable_client_t *client = NULL;

    if (request_has_param(request, "uuid")) {
        client = roundtable_server_get_client_by_uuid(srv,
        *uuid_from_string(request_get_param(request, "uuid")));
    } else {
        client = get_client_from_json(srv, body, "user_uuid");
    }
    return client;
}

static response_t make_response(roundtable_client_t *client)
{
    json_object_t *response_body = json_object_create(NULL);
    char *response_body_str = NULL;
    response_t rep = {0};

    json_object_add(response_body, (json_t *) json_string_create("user_uuid",
        uuid_to_string(client->uuid)));
    json_object_add(response_body, (json_t *) json_string_create("username",
        client->username));
    json_object_add(response_body, (json_t *) json_string_create("status",
        client->status == ONLINE ? "ONLINE" : "OFFLINE"));
    response_body_str = json_serialize((json_t *) response_body);
    rep = create_success(200, response_body_str);
    response_add_header(&rep, "Content-Type", "application/json");
    destroy(response_body_str, (json_t *) response_body, NULL);
    return rep;
}

response_t user_route(request_t *request, void *data)
{
    roundtable_server_t *srv = (roundtable_server_t *)data;
    json_object_t *body = (json_object_t *)json_parse(request->body);
    roundtable_client_t *client = NULL;

    if (!IS_METHOD(request, "GET"))
        return create_error(405, "Method not allowed", "Only GET");
    if (!body || !json_object_has_key(body, "user_uuid"))
        return create_error(400, "Invalid body", "Missing 'user_uuid'");
    client = get_client(request, body, srv);
    if (!client)
        return create_error(404, "Client not found", "Sender not found");
    return make_response(client);
}
