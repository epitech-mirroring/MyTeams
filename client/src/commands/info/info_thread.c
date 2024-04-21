/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** info_thread
*/

#include "myclient.h"
#include "logging_client.h"

static void thread_info_response_success(response_t *response)
{
    json_array_t *jarray = (json_array_t *)json_parse(response->body);
    json_object_t *jobj = (json_object_t *)json_array_get(jarray, 0);
    json_string_t *thread_uuid = (json_string_t *)json_object_get(jobj,
        "thread_uuid");
    json_string_t *thread_title = (json_string_t *)json_object_get(jobj,
        "title");
    json_string_t *thread_msg = (json_string_t *)json_object_get(jobj,
        "message");
    json_string_t *sender_uuid = (json_string_t *)json_object_get(jobj,
        "sender_uuid");
    json_number_t *timestamp = (json_number_t *)json_object_get(jobj,
        "timestamp");

    if (thread_uuid == NULL || thread_title == NULL || thread_msg == NULL ||
        sender_uuid == NULL || timestamp == NULL)
        return;
    client_print_thread(thread_uuid->value, sender_uuid->value,
        timestamp->value, thread_title->value, thread_msg->value);
}

static void thread_info_response_error(response_t *response,
    request_data_t *request_data)
{
    json_object_t *jobj = (json_object_t *)json_parse(response->body);
    json_string_t *error = (json_string_t *)json_object_get(jobj,
        "error_name");
    char *team_uuid = request_get_param(request_data->req, "team-uuid");
    char *channel_uuid = request_get_param(request_data->req, "channel-uuid");
    char *thread_uuid = request_get_param(request_data->req, "thread-uuid");

    if (error == NULL || team_uuid == NULL || channel_uuid == NULL ||
        thread_uuid == NULL)
        return;
    if (strstr(error->value, "Team") != NULL)
        client_error_unknown_team(team_uuid);
    if (strstr(error->value, "Channel") != NULL)
        client_error_unknown_channel(channel_uuid);
    if (strstr(error->value, "Thread") != NULL)
        client_error_unknown_thread(thread_uuid);
}

void thread_info_response(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;

    cli->waiting_for_response = false;
    if (response->status == 200) {
        thread_info_response_success(response);
    }
    if (response->status == 404) {
        thread_info_response_error(response, request_data);
    }
    if (response->status == 403) {
        client_error_unauthorized();
    }
}

void info_thread(client_t *client)
{
    request_t *request = calloc(1, sizeof(request_t));
    char *bearer = add_bearer(client->user_uuid, client->instance_id);

    if (bearer == NULL || request == NULL)
        return;
    request->route = (route_t){"GET", "/teams/channels/threads"};
    request->body = strdup("");
    request_add_header(request, "Authorization", bearer);
    request_add_param(request, "team-uuid", client->context->team_uuid);
    request_add_param(request, "channel-uuid", client->context->channel_uuid);
    request_add_param(request, "thread-uuid", client->context->thread_uuid);
    api_client_send_request(client->api_handler, request,
        &thread_info_response, client);
    client->waiting_for_response = true;
}
