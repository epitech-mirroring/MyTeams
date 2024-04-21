/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** events
*/

#include "myclient.h"
#include "logging_client.h"
#include "teams_events.h"

const event_binding_t event_bindings[] = {
    {LOGGED_IN, &logged_in_callback},
    {LOGGED_OUT, &logged_out_callback},
    {DM_RECEIVED, &dm_received_callback},
    {TEAM_CREATED, &team_created_callback},
    {CHANNEL_CREATED, &channel_created_callback},
    {THREAD_CREATED, &thread_created_callback},
    {THREAD_REPLIED, &thread_replied_callback},
    {NONE, NULL}
};

static void handle_events_callback(json_object_t *data,
    client_event_t event, client_t *client)
{
    for (size_t i = 0; event_bindings[i].event != NONE; i++) {
        if (event_bindings[i].event == event) {
            event_bindings[i].callback(data, client);
            break;
        }
    }
}

static void handle_events(json_array_t *arr, client_t *client)
{
    json_object_t *event = NULL;
    json_number_t *type = NULL;
    json_object_t *data = NULL;

    for (size_t i = 0; i < arr->size; i++) {
        event = (json_object_t *)json_array_get(arr, i);
        if (event == NULL)
            return;
        type = (json_number_t *)json_object_get(event, "type");
        data = (json_object_t *)json_object_get(event, "data");
        if (type == NULL || data == NULL)
            return;
        handle_events_callback(data, type->value, client);
    }
}

void events_response(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;
    json_array_t *arr = NULL;

    if (response->status == 200) {
        arr = (json_array_t *)json_parse(response->body);
        if (arr == NULL || arr->size == 0)
            return;
        handle_events(arr, cli);
    }
    cli->is_event = false;
}

void send_events(client_t *client)
{
    char *bearer = NULL;
    request_t *request = calloc(1, sizeof(request_t));

    if (request == NULL)
        return;
    request->route = (route_t){"GET", "/events"};
    request->body = strdup("");
    if (client->user_uuid != NULL) {
        bearer = add_bearer(client->user_uuid);
        if (bearer != NULL)
            request_add_header(request, "Authorization", bearer);
    }
    api_client_send_request(client->api_handler, request, &events_response,
        client);
}
