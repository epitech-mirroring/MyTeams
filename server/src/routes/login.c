/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"
#include "server_utils.h"
#include "network/dto.h"

static roundtable_client_instance_t *get_create_client(
    roundtable_server_t *server, const char *username, response_t *response)
{
    roundtable_client_t *client = roundtable_server_get_client_by_username(
        server, username);

    if (!client) {
        client = roundtable_server_create_client(server, username);
        *response = create_success(201, "");
        server_event_user_created(uuid_to_string(client->uuid), username);
    } else {
        *response = create_success(200, "");
    }
    server_event_user_logged_in(uuid_to_string(client->uuid));
    client->status = ONLINE;
    roundtable_event_logged_in(server, client);
    return roundtable_client_instance_create(server, client);
}

response_t login_route(request_t *request, void *data)
{
    response_t r = {0};
    roundtable_server_t *s = (roundtable_server_t *) data;
    json_object_t *body = (json_object_t *) json_parse(request->body);
    roundtable_client_instance_t *c = NULL;
    json_object_t *response_body = json_object_create(NULL);

    if (strcmp(request->route.method, "POST") != 0)
        return create_error(405, "Method not allowed", "Only POST");
    if (body == NULL || !json_object_has_key(body, "username"))
        return create_error(400, "Invalid body", "Missing 'username'");
    c = get_create_client(s,
        ((json_string_t *) json_object_get(body, "username"))->value, &r);
    json_object_add(response_body, (json_t *)
        json_string_create("user_uuid", uuid_to_string(c->client->uuid)));
    json_object_add(response_body, (json_t *)
        json_number_create("instance_id", (long) c->instance_number));
    r.body = strdup(json_serialize((json_t *) response_body));
    response_add_header(&r, "Content-Type", "application/json");
    destroy(NULL, (json_t *) body, (json_t *) response_body);
    return r;
}
