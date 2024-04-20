/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** unsubscribe
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

void unsubscribe_response_error(response_t *response,
    request_data_t *request_data)
{
    json_object_t *jobj = NULL;
    json_string_t *team_uuid = NULL;

    if (response->status == 404) {
        jobj = (json_object_t *)json_parse(request_data->req->body);
        team_uuid = (json_string_t *)json_object_get(jobj, "team_uuid");
        if (team_uuid == NULL)
            return;
        client_error_unknown_team(team_uuid->value);
    }
    if (response->status == 401)
        client_error_unauthorized();
}

void unsubscribe_response(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;
    json_object_t *jobj = NULL;
    json_string_t *team_uuid = NULL;

    cli->waiting_for_response = false;
    if (response->status == 204) {
        jobj = (json_object_t *)json_parse(request_data->req->body);
        team_uuid = (json_string_t *)json_object_get(jobj, "team_uuid");
        if (team_uuid == NULL)
            return;
        client_print_unsubscribed(cli->user_uuid, team_uuid->value);
    }
    unsubscribe_response_error(response, request_data);
}

static void send_unsubscribe(client_t *client, char *team_uuid)
{
    request_t *request = calloc(1, sizeof(request_t));
    json_object_t *jobj = json_object_create("root");
    json_string_t *uuid = json_string_create("team_uuid", team_uuid);
    char *bearer = add_bearer(client->user_uuid);

    if (bearer == NULL || request == NULL || jobj == NULL || uuid == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    json_object_add(jobj, (json_t *)uuid);
    request->route = (route_t){"POST", "/teams/leave"};
    request->body = json_serialize((json_t *)jobj);
    request_add_header(request, "Authorization", bearer);
    api_client_send_request(client->api_handler, request,
    &unsubscribe_response, client);
    client->waiting_for_response = true;
}

void unsubscribe(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len != 2) {
        printf("Usage: /unsubscribe [team_uuid]\n");
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
    send_unsubscribe(client, parsed_cmd[1]);
}