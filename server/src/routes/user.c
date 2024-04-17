/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"
#include "server.h"
#include "network/router.h"
#include "json/json.h"
#include "server_utils.h"

static char* params_to_uuid(param_t *params)
{
    char *uuid = NULL;

    for (int i = 0; PARAMS_MAX; i++){
        if (!strcmp(params[i].key, "user_uuid")) {
            uuid = strdup(params[i].value);
            break;
        }
        params++;
    }
    return uuid;
}

response_t *user_route(request_t *request)
{
    response_t *response = calloc(1, sizeof(response_t));
    roundtable_server_t *server = (roundtable_server_t *)request->data;
    json_object_t *req_body = (json_object_t *) json_parse(request->body);
    char *username = NULL;
    char  *uuid_json_user_info = NULL;
    roundtable_client_t *client = NULL;
    json_object_t *rep_body = json_object_create(NULL);
    char *response_body_str = NULL;

    if (!req_body || !json_object_get(req_body, "user_uuid"))
        return create_error(400, "Bad Request", "Invalid JSON body");
    uuid_json_user_info = params_to_uuid(request->params);
    if (!uuid_json_user_info)
    uuid_json_user_info = ((json_string_t *) json_object_get(req_body,
    "user_uuid"))->value;
    client = roundtable_server_get_client_by_uuid(server,
    *uuid_from_string(uuid_json_user_info));
    if (!client)
        return create_error(404, "Not Found", "User not found");
    json_object_add(rep_body, (json_t *) json_string_create("uuid",
    client->username));
    json_object_add(rep_body, (json_t *) json_string_create("name",
    client->status == ONLINE ? "online" : "offline"));
    json_object_add(rep_body, (json_t *) json_string_create("status",
    client->status == ONLINE ? "online" : "offline"));
    response_body_str = json_serialize((json_t *) rep_body);
    response->header.content_length = strlen(response_body_str);
    response->body = strdup(response_body_str);
    destroy(response_body_str, (json_t *) req_body, (json_t *) rep_body);
}