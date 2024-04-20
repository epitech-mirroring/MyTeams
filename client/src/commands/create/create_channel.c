/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** create_channel
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

void create_channel_response_success(response_t *response,
    request_data_t *request_data)
{
    json_object_t *jobj_resp = (json_object_t *)json_parse(response->body);
    json_object_t *jobj_send =
        (json_object_t *)json_parse(request_data->req->body);
    json_string_t *channel_uuid =
        (json_string_t *)json_object_get(jobj_resp, "channel_uuid");
    json_string_t *channel_name =
        (json_string_t *)json_object_get(jobj_send, "name");
    json_string_t *channel_desc =
        (json_string_t *)json_object_get(jobj_send, "description");

    if (jobj_resp == NULL || jobj_send == NULL || channel_uuid == NULL ||
        channel_name == NULL || channel_desc == NULL)
        return;
    client_print_channel_created(channel_uuid->value, channel_name->value,
        channel_desc->value);
}

void create_channel_response(response_t *response,
    request_data_t *request_data)
{
    client_t *client = (client_t *)request_data->data;

    client->waiting_for_response = false;
    if (response->status == 201) {
        create_channel_response_success(response, request_data);
    }
    if (response->status == 401 || response->status == 403)
        client_error_unauthorized();
    if (response->status == 404)
        client_error_unknown_team(client->context->team_uuid);
}

static void send_create_channel(client_t *client, char *name,
    char *description)
{
    request_t *request = calloc(1, sizeof(request_t));
    json_object_t *jobj = json_object_create("root");
    json_string_t *team_uuid = json_string_create("team_uuid",
        client->context->team_uuid);
    json_string_t *chan_name = json_string_create("name", name);
    json_string_t *chan_desc = json_string_create("description", description);
    char *bearer = add_bearer(client->user_uuid);

    if (bearer == NULL || request == NULL || jobj == NULL ||
        team_uuid == NULL || chan_name == NULL || chan_desc == NULL)
        return;
    json_object_add(jobj, (json_t *)chan_name);
    json_object_add(jobj, (json_t *)chan_desc);
    json_object_add(jobj, (json_t *)team_uuid);
    request->route = (route_t){"POST", "/teams/channels/create"};
    request->body = json_serialize((json_t *)jobj);
    request_add_header(request, "Authorization", bearer);
    api_client_send_request(client->api_handler, request,
    &create_channel_response, client);
    client->waiting_for_response = true;
}

void create_channel(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len != 3) {
        printf("Invalid number of arguments\n");
        return;
    }
    len = strlen(parsed_cmd[1]);
    if (len < 1 || len > MAX_NAME_LENGTH) {
        printf("Error: channel name must be between 1 and %d characters\n",
            MAX_NAME_LENGTH);
        return;
    }
    len = strlen(parsed_cmd[2]);
    if (len < 1 || len > MAX_DESCRIPTION_LENGTH) {
        printf("Error: channel description must be between 1 and %d "
            "characters\n", MAX_DESCRIPTION_LENGTH);
        return;
    }
    send_create_channel(client, parsed_cmd[1], parsed_cmd[2]);
}
