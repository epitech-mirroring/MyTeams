/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list_replies
*/

#include "myclient.h"
#include "logging_client.h"

static void display_replies(json_array_t *arr, request_data_t *request_data)
{
    char *thread_uuid = request_get_param(request_data->req, "thread-uuid");
    json_object_t *obj = NULL;
    json_string_t *sender_uuid = NULL;
    json_number_t *timestamp = NULL;
    json_string_t *content = NULL;

    for (size_t i = 0; i < arr->size; i++) {
        obj = (json_object_t *)json_array_get(arr, i);
        sender_uuid = (json_string_t *)json_object_get(obj, "sender_uuid");
        timestamp = (json_number_t *)json_object_get(obj, "timestamp");
        content = (json_string_t *)json_object_get(obj, "content");
        if (sender_uuid == NULL || timestamp == NULL || content == NULL)
            return;
        client_thread_print_replies(thread_uuid, sender_uuid->value,
            timestamp->value, content->value);
    }
}

static void list_replies_response_error(response_t *response,
    request_data_t *request_data)
{
    json_object_t *obj = (json_object_t *)json_parse(response->body);
    json_string_t *error = (json_string_t *)json_object_get(obj, "error_name");
    char *team_uuid = request_get_param(request_data->req, "team-uuid");
    char *channel_uuid = request_get_param(request_data->req, "channel-uuid");
    char *thread_uuid = request_get_param(request_data->req, "thread-uuid");

    if (error == NULL || team_uuid == NULL || channel_uuid == NULL)
        return;
    if (strstr(error->value, "Team") != NULL)
        client_error_unknown_team(team_uuid);
    if (strstr(error->value, "Channel") != NULL)
        client_error_unknown_channel(channel_uuid);
    if (strstr(error->value, "Thread") != NULL)
        client_error_unknown_thread(thread_uuid);
}

void list_replies_response(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;
    json_array_t *arr = NULL;

    cli->waiting_for_response = false;
    if (response->status == 200) {
        arr = (json_array_t *)json_array_parse(response->body);
        if (arr == NULL)
            return;
        display_replies(arr, request_data);
    }
    if (response->status == 403) {
        client_error_unauthorized();
    }
    if (response->status == 404) {
        list_replies_response_error(response, request_data);
    }
}

void list_replies(client_t *client)
{
    request_t *request = calloc(1, sizeof(request_t));
    char *bearer = add_bearer(client->user_uuid, client->instance_id);

    if (bearer == NULL || request == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    request->route = (route_t){"GET", "/teams/channels/threads/messages"};
    request->body = strdup("");
    request_add_header(request, "Authorization", bearer);
    request_add_param(request, "thread-uuid", client->context->thread_uuid);
    request_add_param(request, "channel-uuid", client->context->channel_uuid);
    request_add_param(request, "team-uuid", client->context->team_uuid);
    api_client_send_request(client->api_handler, request,
        &list_replies_response, client);
    client->waiting_for_response = true;
}
