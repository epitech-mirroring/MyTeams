/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list_threads
*/

#include "myclient.h"
#include "logging_client.h"

static void display_one_thread(json_object_t *obj)
{
    json_string_t *uuid = (json_string_t *)json_object_get(obj, "thread_uuid");
    json_string_t *title = (json_string_t *)json_object_get(obj, "title");
    json_string_t *user_uuid = (json_string_t *)json_object_get(obj,
        "sender_uuid");
    json_number_t *timestamp = (json_number_t *)json_object_get(obj,
        "timestamp");
    json_string_t *message = (json_string_t *)json_object_get(obj, "message");

    if (uuid == NULL || title == NULL || user_uuid == NULL ||
        timestamp == NULL || message == NULL)
        return;
    client_channel_print_threads(uuid->value, user_uuid->value,
        timestamp->value, title->value, message->value);
}

static void display_threads(json_array_t *arr)
{
    json_object_t *obj = NULL;

    for (size_t i = 0; i < arr->size; i++) {
        obj = (json_object_t *)json_array_get(arr, i);
        if (obj == NULL)
            return;
        display_one_thread(obj);
    }
}

static void list_threads_response_error(response_t *response,
    request_data_t *request_data)
{
    json_object_t *jobj = (json_object_t *)json_parse(response->body);
    json_string_t *error = (json_string_t *)json_object_get(jobj,
        "error_name");
    char *team_uuid = request_get_param(request_data->req, "team-uuid");
    char *channel_uuid = request_get_param(request_data->req, "channel-uuid");

    if (error == NULL || team_uuid == NULL || channel_uuid == NULL)
        return;
    if (strstr(error->value, "Team") != NULL)
        client_error_unknown_team(team_uuid);
    if (strstr(error->value, "Channel") != NULL)
        client_error_unknown_channel(channel_uuid);
}

void list_threads_response(response_t *response, request_data_t *request_data)
{
    client_t *client = (client_t *)request_data->data;
    json_array_t *arr = NULL;

    client->waiting_for_response = false;
    if (response->status == 200) {
        arr = (json_array_t *)json_array_parse(response->body);
        if (arr == NULL)
            return;
        display_threads(arr);
    }
    if (response->status == 403) {
        client_error_unauthorized();
    }
    if (response->status == 404) {
        list_threads_response_error(response, request_data);
    }
}

void list_threads(client_t *client)
{
    request_t *request = calloc(1, sizeof(request_t));
    char *bearer = add_bearer(client->user_uuid, client->instance_id);

    if (request == NULL || bearer == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    request->route = (route_t){"GET", "/teams/channels/threads"};
    request->body = strdup("");
    request_add_header(request, "Authorization", bearer);
    request_add_param(request, "team-uuid", client->context->team_uuid);
    request_add_param(request, "channel-uuid", client->context->channel_uuid);
    api_client_send_request(client->api_handler, request,
        &list_threads_response, client);
    client->waiting_for_response = true;
}
