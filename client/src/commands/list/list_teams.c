/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list_teams
*/

#include "myclient.h"
#include "logging_client.h"

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

void list_teams_response(response_t *response, request_data_t *request_data)
{
    client_t *client = (client_t *)request_data->data;
    json_array_t *arr = NULL;

    client->waiting_for_response = false;
    if (response->status == 200) {
        arr = (json_array_t *)json_array_parse(response->body);
        if (arr == NULL)
            return;
        display_teams(arr);
    }
    if (response->status == 401) {
        client_error_unauthorized();
    }
}

void list_teams(client_t *client)
{
    request_t *request = calloc(1, sizeof(request_t));
    char *bearer = add_bearer(client->user_uuid, client->instance_id);

    if (bearer == NULL || request == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    request->route = (route_t){"GET", "/teams"};
    request->body = strdup("");
    request_add_header(request, "Authorization", bearer);
    api_client_send_request(client->api_handler, request,
        &list_teams_response, client);
    client->waiting_for_response = true;
}
