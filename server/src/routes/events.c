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

static json_object_t *dto_event(events_t *event)
{
    json_object_t *json = json_object_create(NULL);
    json_number_t *type = json_number_create("type", event->type);
    json_object_t *data = event->data;

    json_object_add(json, (json_t *) type);
    json_object_add(json, (json_t *) data);
    return json;
}

response_t events_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    roundtable_client_t *client = NULL;
    json_array_t *response_body = json_array_create(NULL);
    char *response_body_str = NULL;

    if (strcmp(request->route.method, "GET") != 0)
        return create_error(405, "Method not allowed", "Only POST");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    client = get_client_from_header(server, request);
    if (client == NULL)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    for (size_t i = 0; i < client->event_count; i++) {
        json_array_add(response_body, (json_t *) dto_event(client->events[i]));
    }
    response_body_str = json_serialize((json_t *) response_body);
    json_destroy((json_t *) response_body);
    roundtable_server_clear_events(server, client);
    return create_success(200, response_body_str);
}
