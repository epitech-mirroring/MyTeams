/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"
#include "network/router.h"
#include "json/json.h"
#include "server_utils.h"

static roundtable_client_t *get_or_create_client(
    roundtable_server_t *server, const char *username, response_t *response)
{
    roundtable_client_t *client = roundtable_server_get_client_by_username(
        server, username);

    if (!client) {
        client = roundtable_server_create_client(server, username);
        if (response)
            response->header.status_code = 201;
    } else {
        if (response)
            response->header.status_code = 200;
    }
    client->status = ONLINE;
    return client;
}

static void destroy(char *str, json_t *req_body, json_t *res_body)
{
    free(str);
    json_destroy(req_body);
    json_destroy(res_body);
}

response_t *login_route(request_t *request)
{
    response_t *response = calloc(1, sizeof(response_t));
    roundtable_server_t *server = (roundtable_server_t *)request->data;
    json_object_t *body = (json_object_t *) json_parse(request->body);
    char *username = NULL;
    roundtable_client_t *client = NULL;
    json_object_t *response_body = json_object_create(NULL);
    json_string_t *uuid_json = NULL;
    char *response_body_str = NULL;

    if (!body || !json_object_get(body, "username"))
        return create_error(400, "Bad Request", "Invalid JSON body");
    username = ((json_string_t *) json_object_get(body, "username"))->value;
    client = get_or_create_client(server, username, response);
    uuid_json = json_string_create("uuid", uuid_to_string(client->uuid));
    json_object_add(response_body, (json_t *) uuid_json);
    response_body_str = json_serialize((json_t *) response_body);
    response->header.content_length = strlen(response_body_str);
    response->body = strdup(response_body_str);
    destroy(response_body_str, (json_t *) body, (json_t *) response_body);
    return response;
}
