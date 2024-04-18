/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdio.h>
#include "server.h"
#include "json/json.h"
#include "server_utils.h"
#include "network/dto.h"

static roundtable_client_t *get_or_create_client(
    roundtable_server_t *server, const char *username, response_t *response)
{
    roundtable_client_t *client = roundtable_server_get_client_by_username(
        server, username);

    if (!client) {
        client = roundtable_server_create_client(server, username);
        response->status = 201;
        response->status_message = strdup("Created");
    } else {
        response->status = 200;
        response->status_message = strdup("OK");
    }
    client->status = ONLINE;
    return client;
}

response_t login_route(request_t *request, void *data)
{
    response_t response = {0};
    roundtable_server_t *server = (roundtable_server_t *) data;
    json_object_t *body = (json_object_t *) json_parse(request->body);
    char *username = NULL;
    roundtable_client_t *client = NULL;
    json_object_t *response_body = json_object_create(NULL);
    json_string_t *uuid_json = NULL;
    char *response_body_str = NULL;

    if (body == NULL || !json_object_has_key(body, "username"))
        return create_error(400, "Bad Request", "Bad Request",
            "Invalid JSON body");
    username = ((json_string_t *) json_object_get(body, "username"))->value;
    client = get_or_create_client(server, username, &response);
    uuid_json = json_string_create("uuid", uuid_to_string(client->uuid));
    json_object_add(response_body, (json_t *) uuid_json);
    response_body_str = json_serialize((json_t *) response_body);
    response.body = strdup(response_body_str);
    response_add_header(&response, "Content-Type", "application/json");
    destroy(response_body_str, (json_t *) body, (json_t *) response_body);
    return response;
}
