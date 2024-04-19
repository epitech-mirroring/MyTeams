/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** create_team
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

void create_team_response_success(response_t *response,
    request_data_t *request_data)
{
    json_object_t *jobj_resp = (json_object_t *)json_parse(response->body);
    json_object_t *jobj_send =
        (json_object_t *)json_parse(request_data->req->body);
    json_string_t *team_uuid =
        (json_string_t *)json_object_get(jobj_resp, "team_uuid");
    json_string_t *team_name =
        (json_string_t *)json_object_get(jobj_send, "name");
    json_string_t *team_desc =
        (json_string_t *)json_object_get(jobj_send, "description");

    if (jobj_resp == NULL || jobj_send == NULL || team_uuid == NULL ||
        team_name == NULL || team_desc == NULL)
        return;
    client_print_team(team_uuid->value, team_name->value, team_desc->value);
}

void create_team_response(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;

    cli->waiting_for_response = false;
    if (response->status == 201) {
        create_team_response_success(response, request_data);
    }
    if (response->status == 401) {
        client_error_unauthorized();
    }
}

static void send_create_team(client_t *client, char *team_name,
    char *team_desc)
{
    request_t *request = calloc(1, sizeof(request_t));
    json_object_t *jobj = json_object_create("root");
    json_string_t *name = json_string_create("name", team_name);
    json_string_t *desc = json_string_create("description", team_desc);
    char *bearer = add_bearer(client->user_uuid);

    if (bearer == NULL || request == NULL || jobj == NULL ||
        name == NULL || desc == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    json_object_add(jobj, (json_t *)name);
    json_object_add(jobj, (json_t *)desc);
    request->route = (route_t){"POST", "/teams/create"};
    request->body = json_serialize((json_t *)jobj);
    request_add_header(request, "Authorization", bearer);
    api_client_send_request(client->api_handler, request,
    &create_team_response, client);
    client->waiting_for_response = true;
}

void create_team(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len != 3) {
        printf("Invalid number of arguments\n");
        return;
    }
    len = strlen(parsed_cmd[1]);
    if (len < 1 || len > MAX_NAME_LENGTH) {
        printf("Error: team name must be between 1 and %d characters\n",
            MAX_NAME_LENGTH);
        return;
    }
    len = strlen(parsed_cmd[2]);
    if (len < 1 || len > MAX_DESCRIPTION_LENGTH) {
        printf("Error: team description must be between 1 and %d characters\n",
            MAX_DESCRIPTION_LENGTH);
        return;
    }
    send_create_team(client, parsed_cmd[1], parsed_cmd[2]);
}
