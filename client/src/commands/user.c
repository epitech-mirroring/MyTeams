/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** user
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

void user_sucess_resp(json_object_t *jobj)
{
    json_string_t *uuid = NULL;
    json_string_t *username = NULL;
    json_string_t *status = NULL;

    if (jobj == NULL)
        return;
    uuid = (json_string_t *)json_object_get(jobj, "uuid");
    username = (json_string_t *)json_object_get(jobj, "name");
    status = (json_string_t *)json_object_get(jobj, "status");
    if (uuid == NULL || username == NULL || status == NULL) {
        printf("Error: invalid response\n");
        return;
    }
    client_print_user(uuid->value, username->value,
        (status->value[1] == 'N' ? 1 : 0));
}

void user_response(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;
    json_object_t *jobj = NULL;
    json_string_t *uuid = NULL;
    json_string_t *username = NULL;
    json_string_t *status = NULL;

    cli->waiting_for_response = false;
    if (response->status == 200) {
        jobj = (json_object_t *)json_parse(response->body);
        user_sucess_resp(jobj);
    }
    if (response->status == 404) {
        client_error_unknown_user(
            request_get_param(request_data->req, "uuid"));
    }
}

static void send_user(client_t *client, char *uuid)
{
    json_object_t *jobj = json_object_create("root");
    json_string_t *user = json_string_create("user_uuid", client->user_uuid);
    request_t *request = calloc(1, sizeof(request_t));

    if (jobj == NULL || user == NULL || request == NULL)
        return;
    json_object_add(jobj, (json_t *)user);
    request->route = (route_t){"GET", "/user"};
    request->body = json_serialize((json_t *)jobj);
    request_add_param(request, "uuid", uuid);
    api_client_send_request(client->api_handler, request, &user_response,
        client);
    client->waiting_for_response = true;
}

void user(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len != 2) {
        printf("Usage: /user [\"user_uuid\"]\n");
        return;
    }
    if (uuid_from_string(parsed_cmd[1]) == NULL) {
        printf("Error: invalid uuid\n");
        return;
    }
    if (client->is_logged == false) {
        client_error_unauthorized();
        return;
    }
    send_user(client, parsed_cmd[1]);
}
