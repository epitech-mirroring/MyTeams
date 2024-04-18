/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** login
*/

#include "myclient.h"
#include "json/json.h"
#include "logging_client.h"

void logout_rep(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;
    json_object_t *jobj = NULL;
    json_string_t *str = NULL;

    cli->waiting_for_response = false;
    if (response->status == 204) {
        client_event_logged_out(cli->user_uuid, cli->user_name);
        cli->is_logged = false;
        cli->user_uuid = NULL;
    } else {
        jobj = (json_object_t *)json_parse(response->body);
        str = (json_string_t *)json_object_get(jobj, "error_message");
        printf("Error: %s\n", str->value);
        json_destroy((json_t *)jobj);
    }
}

static void request_logout(client_t *client)
{
    json_object_t *jobj = json_object_create("root");
    json_string_t *uuid = json_string_create("user_uuid", client->user_uuid);
    request_t *request = calloc(1, sizeof(request_t));

    if (jobj == NULL || uuid == NULL || request == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    json_object_add(jobj, (json_t *)uuid);
    request->route = (route_t){"POST", "/logout"};
    request->body = json_serialize((json_t *)jobj);
    api_client_send_request(client->api_handler, request, &logout_rep, client);
    client->waiting_for_response = true;
}

void logout(char **parsed_cmd, client_t *client)
{
    size_t len = tab_len(parsed_cmd);

    if (len > 1) {
        printf("Usage: /logout\n");
        return;
    }
    if (client->is_logged == false) {
        printf("You are not logged in\n");
        return;
    }
    request_logout(client);
}
