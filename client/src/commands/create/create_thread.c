/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** create_thread
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

static void create_thread_response_error(response_t *response,
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

    if (error == NULL)
        return;
    if (strstr(error->value, "Team") != NULL)
        client_error_unknown_team(team_uuid->value);
    if (strstr(error->value, "Channel") != NULL)
        client_error_unknown_channel(chan_uuid->value);
}

static void create_thread_response_success(response_t *response,
    request_data_t *request)
{
    client_t *cli = (client_t *)request->data;
    json_object_t *jobj_resp = (json_object_t *)json_parse(response->body);
    json_object_t *jobj_send = (json_object_t *)json_parse(request->req->body);
    json_string_t *thread_uuid =
        (json_string_t *)json_object_get(jobj_resp, "thread_uuid");
    json_number_t *thread_ts =
        (json_number_t *)json_object_get(jobj_resp, "timestamp");
    json_string_t *thread_title =
        (json_string_t *)json_object_get(jobj_send, "title");
    json_string_t *thread_body =
        (json_string_t *)json_object_get(jobj_send, "message");

    if (jobj_resp == NULL || jobj_send == NULL || thread_uuid == NULL ||
        thread_title == NULL || thread_body == NULL || thread_ts == NULL)
        return;
    client_print_thread_created(thread_uuid->value, cli->user_uuid,
        thread_ts->value, thread_title->value, thread_body->value);
}

void create_thread_response(response_t *response, request_data_t *request_data)
{
    client_t *client = (client_t *)request_data->data;

    client->waiting_for_response = false;
    if (response->status == 201) {
        create_thread_response_success(response, request_data);
    }
    if (response->status == 401 || response->status == 403) {
        client_error_unauthorized();
    }
    if (response->status == 404) {
        create_thread_response_error(response, request_data);
    }
}

static json_object_t *create_thread_json(char *team_uuid, char *chan_uuid,
    char *title, char *body)
{
    json_object_t *jobj = json_object_create("root");
    json_string_t *team_uuid_json = json_string_create("team_uuid", team_uuid);
    json_string_t *chan_uuid_json =
        json_string_create("channel_uuid", chan_uuid);
    json_string_t *thread_title = json_string_create("title", title);
    json_string_t *thread_body = json_string_create("message", body);

    if (jobj == NULL || team_uuid_json == NULL || chan_uuid_json == NULL ||
        thread_title == NULL || thread_body == NULL) {
        return NULL;
    }
    json_object_add(jobj, (json_t *)team_uuid_json);
    json_object_add(jobj, (json_t *)chan_uuid_json);
    json_object_add(jobj, (json_t *)thread_title);
    json_object_add(jobj, (json_t *)thread_body);
    return jobj;
}

static void send_create_thread(client_t *client, const char *title,
    const char *body)
{
    request_t *request = calloc(1, sizeof(request_t));
    json_object_t *jobj = create_thread_json(client->context->team_uuid,
        client->context->channel_uuid, title, body);
    char *bearer = add_bearer(client->user_uuid);

    if (bearer == NULL || request == NULL || jobj == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    request->route = (route_t){"POST", "/teams/channels/threads/create"};
    request->body = json_serialize((json_t *)jobj);
    request_add_header(request, "Authorization", bearer);
    api_client_send_request(client->api_handler, request,
        &create_thread_response, client);
    client->waiting_for_response = true;
}

void create_thread(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len != 3) {
        printf("Invalid number of arguments\n");
        return;
    }
    len = strlen(parsed_cmd[2]);
    if (len < 1 || len > MAX_BODY_LENGTH) {
        printf("Error: thread body length must be between 1 and %d\n",
            MAX_BODY_LENGTH);
        return;
    }
    send_create_thread(client, parsed_cmd[1], parsed_cmd[2]);
}
