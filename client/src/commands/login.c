/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** login
*/

#include "myclient.h"
#include "json/json.h"
#include "network/networking.h"
#include "logging_client.h"

void login_resp(response_t *response, void *client)
{
    client_t *cli = (client_t *)client;
    json_object_t *jobj = NULL;
    json_string_t *str = NULL;

    cli->waiting_for_response = false;
    if (response->header.status_code == 200 ||
        response->header.status_code == 201) {
        jobj = (json_object_t *)json_parse(response->body);
        if (jobj == NULL) {
            return;
        }
        str = (json_string_t *)json_object_get(jobj, "user_uuid");
        if (str == NULL) {
            printf("Error: invalid response\n");
            return;
        }
        cli->user_uuid = strdup(str->value);
        cli->is_logged = true;
        client_event_logged_in(cli->user_uuid, cli->user_name);
    }
}

static void send_login(client_t *client, char *user_name)
{
    json_object_t *jobj = json_object_create("root");
    json_string_t *username = json_string_create("username", user_name);
    request_t *request = NULL;

    if (jobj == NULL || username == NULL) {
        return;
    }
    json_object_add(jobj, (json_t *)username);
    request = network_create_request_no_params((route_t){POST, "/login"}, (json_t *)jobj);
    if (request == NULL) {
        return;
    }
    network_send_request(client->api_handler, request, &login_resp, client);
    client->waiting_for_response = true;
    client->user_name = strdup(user_name);
}

void login(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);
    int name_len = 0;

    if (len != 2) {
        printf("Usage: /login [\"username\"]\n");
        return;
    }
    if (client->is_logged == true) {
        printf("You are already logged in\n");
        return;
    }
    name_len = strlen(parsed_cmd[1]);
    if (name_len < 1 || name_len > MAX_NAME_LENGTH) {
        printf("Error: username must be between 1 and %i characters\n", MAX_NAME_LENGTH);
        return;
    }
    send_login(client, parsed_cmd[1]);
}
