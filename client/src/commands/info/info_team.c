/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** info_team
*/

#include "myclient.h"
#include "logging_client.h"

static void team_info_response_success(response_t *response)
{
    json_array_t *jarray = (json_array_t *)json_parse(response->body);
    json_object_t *jobj_resp = (json_object_t *)json_array_get(jarray, 0);
    json_string_t *team_uuid = (json_string_t *)json_object_get(jobj_resp,
        "team_uuid");
    json_string_t *team_name = (json_string_t *)json_object_get(jobj_resp,
        "team_name");
    json_string_t *team_desc = (json_string_t *)json_object_get(jobj_resp,
        "team_description");

    if (jobj_resp == NULL || team_uuid == NULL || team_name == NULL ||
        team_desc == NULL)
        return;
    client_print_team(team_uuid->value, team_name->value, team_desc->value);
}

void team_info_response(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;

    cli->waiting_for_response = false;
    if (response->status == 200) {
        team_info_response_success(response);
    }
    if (response->status == 404) {
        client_error_unknown_team(cli->context->team_uuid);
    }
}

void info_team(client_t *client)
{
    request_t *request = calloc(1, sizeof(request_t));
    char *bearer = add_bearer(client->user_uuid, client->instance_id);

    if (bearer == NULL || request == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    request->route = (route_t){"GET", "/teams"};
    request_add_header(request, "Authorization", bearer);
    request_add_param(request, "team-uuid", client->context->team_uuid);
    request->body = strdup("");
    api_client_send_request(client->api_handler, request, &team_info_response,
        client);
    client->waiting_for_response = true;
}
