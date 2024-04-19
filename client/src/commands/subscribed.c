/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** subscribed
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

static void display_teams(json_array_t *arr)
{
    int i = 0;
    json_object_t *team = NULL;
    json_string_t *t_uuid = NULL;
    json_string_t *t_name = NULL;
    json_string_t *t_desc = NULL;

    do {
        team = (json_object_t *)json_array_get(arr, i);
        if (team == NULL)
            return;
        t_uuid = (json_string_t *)json_object_get(team, "team_uuid");
        t_name = (json_string_t *)json_object_get(team, "team_name");
        t_desc = (json_string_t *)json_object_get(team, "team_description");
        if (t_uuid == NULL || t_name == NULL || t_desc == NULL) {
            return;
        }
        client_print_teams(t_uuid->value, t_name->value, t_desc->value);
        i++;
    } while (1);
}

void subscribed_response(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;
    json_array_t *arr = NULL;

    cli->waiting_for_response = false;
    if (response->status == 200) {
        arr = (json_array_t *)json_array_parse(response->body);
        if (arr == NULL)
            return;
        display_teams(arr);
    }
}

static void display_users(json_array_t *arr)
{
    int i = 0;
    json_object_t *user = NULL;
    json_string_t *uuid = NULL;
    json_string_t *username = NULL;
    json_string_t *status = NULL;

    do {
        user = (json_object_t *)json_array_get(arr, i);
        if (user == NULL)
            return;
        uuid = (json_string_t *)json_object_get(user, "uuid");
        username = (json_string_t *)json_object_get(user, "username");
        status = (json_string_t *)json_object_get(user, "status");
        if (uuid == NULL || username == NULL || status == NULL) {
            return;
        }
        client_print_users(uuid->value, username->value,
            (status->value[1] == 'N' ? 1 : 0));
        i++;
    } while (1);
}

void users_subscribed_response(response_t *response,
    request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;
    json_array_t *arr = NULL;

    cli->waiting_for_response = false;
    if (response->status == 200) {
        arr = (json_array_t *)json_array_parse(response->body);
        if (arr == NULL)
            return;
        display_users(arr);
    }
    if (response->status == 404) {
        client_error_unknown_team(
            request_get_param(request_data->req, "team_uuid"));
    }
    if (response->status == 403) {
        client_error_unauthorized();
    }
}

static void send_subscribed(client_t *client)
{
    request_t *request = calloc(1, sizeof(request_t));
    char *bearer = add_bearer(client->user_uuid);

    if (bearer == NULL || request == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    request->route = (route_t){"GET", "/teams"};
    request->body = strdup("");
    request_add_header(request, "Authorization", bearer);
    request_add_param(request, "only-joined", "true");
    api_client_send_request(client->api_handler, request, &subscribed_response,
        client);
    client->waiting_for_response = true;
}

static void send_users_subscribed(client_t *client, char *team_uuid)
{
    request_t *request = calloc(1, sizeof(request_t));
    char *bearer = add_bearer(client->user_uuid);

    if (bearer == NULL || request == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    request->route = (route_t){"GET", "/teams/users"};
    request->body = strdup("");
    request_add_header(request, "Authorization", bearer);
    request_add_param(request, "team-uuid", team_uuid);
    api_client_send_request(client->api_handler, request,
        &users_subscribed_response, client);
    client->waiting_for_response = true;
}

void subscribed(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len != 1 && len != 2) {
        printf("Usage: /subscribed ?[team_uuid]\n");
        return;
    }
    if (client->is_logged == false) {
        client_error_unauthorized();
        return;
    }
    if (len == 1) {
        send_subscribed(client);
        return;
    }
    if (uuid_from_string(parsed_cmd[1]) == NULL) {
        printf("Error: invalid uuid\n");
        return;
    }
    send_users_subscribed(client, parsed_cmd[1]);
}
