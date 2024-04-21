/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** create_reply
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

static void create_reply_response_error(response_t *response,
    request_data_t *request)
{
    json_object_t *jobj = (json_object_t *)json_parse(response->body);
    json_object_t *jobj_send = (json_object_t *)json_parse(request->req->body);
    json_string_t *error = (json_string_t *)json_object_get(jobj,
        "error_name");
    json_string_t *team_uuid = (json_string_t *)json_object_get(jobj_send,
        "team_uuid");
    json_string_t *chan_uuid = (json_string_t *)json_object_get(jobj_send,
        "channel_uuid");
    json_string_t *thread_uuid = (json_string_t *)json_object_get(jobj_send,
        "thread_uuid");

    if (error == NULL)
        return;
    if (strstr(error->value, "Team") != NULL)
        client_error_unknown_team(team_uuid->value);
    if (strstr(error->value, "Channel") != NULL)
        client_error_unknown_channel(chan_uuid->value);
    if (strstr(error->value, "Thread") != NULL)
        client_error_unknown_thread(thread_uuid->value);
}

static void create_reply_response_success(response_t *response,
    request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;
    json_object_t *jobj_resp = (json_object_t *)json_parse(response->body);
    json_object_t *jobj_send =
        (json_object_t *)json_parse(request_data->req->body);
    json_string_t *thread_uuid =
        (json_string_t *)json_object_get(jobj_send, "thread_uuid");
    json_number_t *thread_ts =
        (json_number_t *)json_object_get(jobj_resp, "timestamp");
    json_object_t *message =
        (json_object_t *)json_object_get(jobj_send, "message");
    json_string_t *message_body =
        (json_string_t *)json_object_get(message, "content");

    if (jobj_resp == NULL || jobj_send == NULL || thread_uuid == NULL ||
        message_body == NULL || thread_ts == NULL)
        return;
    client_print_reply_created(thread_uuid->value, cli->user_uuid,
        thread_ts->value, message_body->value);
}

void create_reply_response(response_t *response,
    request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;

    cli->waiting_for_response = false;
    if (response->status == 201) {
        create_reply_response_success(response, request_data);
    }
    if (response->status == 401 || response->status == 403) {
        client_error_unauthorized();
    }
    if (response->status == 404) {
        create_reply_response_error(response, request_data);
    }
}

static json_object_t *create_reply_json(client_t *client, char *body)
{
    json_object_t *jobj = json_object_create("root");
    json_string_t *team_uuid = json_string_create("team_uuid",
        client->context->team_uuid);
    json_string_t *chan_uuid = json_string_create("channel_uuid",
        client->context->channel_uuid);
    json_string_t *thread_uuid = json_string_create("thread_uuid",
        client->context->thread_uuid);
    json_object_t *jobj_body = json_object_create("message");
    json_string_t *body_str = json_string_create("content", body);

    if (jobj == NULL || team_uuid == NULL || chan_uuid == NULL ||
        thread_uuid == NULL || jobj_body == NULL || body_str == NULL) {
        return NULL;
    }
    json_object_add(jobj, (json_t *)team_uuid);
    json_object_add(jobj, (json_t *)chan_uuid);
    json_object_add(jobj, (json_t *)thread_uuid);
    json_object_add(jobj_body, (json_t *)body_str);
    json_object_add(jobj, (json_t *)jobj_body);
    return jobj;
}

static void send_create_reply(client_t *client, char *body)
{
    request_t *request = calloc(1, sizeof(request_t));
    json_object_t *jobj = create_reply_json(client, body);
    char *bearer = add_bearer(client->user_uuid, client->instance_id);

    if (bearer == NULL || request == NULL || jobj == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    request->route = (route_t){"POST", "/teams/channels/threads/reply"};
    request->body = json_serialize((json_t *)jobj);
    request_add_header(request, "Authorization", bearer);
    api_client_send_request(client->api_handler, request,
        &create_reply_response, client);
    client->waiting_for_response = true;
}

void create_reply(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len != 2) {
        printf("Invalid number of arguments\n");
        return;
    }
    len = strlen(parsed_cmd[1]);
    if (len < 1 || len > MAX_BODY_LENGTH) {
        printf("Error: reply body length must be between 1 and %d\n",
            MAX_BODY_LENGTH);
        return;
    }
    send_create_reply(client, parsed_cmd[1]);
}
