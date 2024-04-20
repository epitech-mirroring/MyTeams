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

    cli->waiting_for_response = false;
    if (response->status == 204) {
        cli->is_logged = false;
        printf("CLI : Successfully logged out\n");
    }
}

static void request_logout(client_t *client)
{
    char *uuid = add_bearer(client->user_uuid);
    request_t *request = calloc(1, sizeof(request_t));

    if (uuid == NULL || request == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    request->route = (route_t){"POST", "/logout"};
    request_add_header(request, "Authorization", uuid);
    request->body = strdup("");
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

void logout_when_leaving(client_t *client)
{
    if (client->is_logged == false)
        return;
    request_logout(client);
}
