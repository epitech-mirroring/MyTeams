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

static bool is_connected(request_t *request, roundtable_server_t *srv)
{
    if (request_has_param(request, "only-connected")) {
        if (strcmp(request_get_param(request, "only-connected"), "true") == 0)
            return true;
    }
    return false;
}

static response_t make_response(roundtable_client_t *client,
    roundtable_server_t *srv, bool only_connected, response_t rep)
{
    char *response_body_str = NULL;
    json_array_t *response_body_array = json_array_create(NULL);
    json_object_t *users = NULL;

    for (size_t i = 0; i < srv->client_count; i++) {
        if (only_connected && srv->clients[i]->status == OFFLINE)
            continue;
        users = json_object_create(NULL);
        json_object_add(users, (json_t *)json_string_create("uuid",
            uuid_to_string(srv->clients[i]->uuid)));
        json_object_add(users, (json_t *)json_string_create("name",
            srv->clients[i]->username));
        json_object_add(users, (json_t *)json_string_create("status",
            status_to_string(srv->clients[i]->status)));
        json_array_add(response_body_array, (json_t *)users);
    }
    response_body_str = json_serialize((json_t *)response_body_array);
    rep = create_success(200, response_body_str);
    destroy(response_body_str, (json_t *)response_body_array, NULL);
    return rep;
}

response_t users_route(request_t *request, void *data)
{
    roundtable_server_t *srv = (roundtable_server_t *)data;
    roundtable_client_instance_t *instance = NULL;
    response_t rep = {0};
    bool only_connected = false;

    if (!IS_METHOD(request, "GET"))
        return create_error(405, "Method not allowed", "Only GET");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    instance = get_instance_from_header(data, request);
    if (!instance)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    only_connected = is_connected(request, srv);
    return make_response(instance->client, srv, only_connected, rep);
}
