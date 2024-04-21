/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list_channels
*/

#include "myclient.h"
#include "logging_client.h"

static void display_channel(json_array_t *arr)
{
    int i = 0;
    json_object_t *channel = NULL;
    json_string_t *c_uuid = NULL;
    json_string_t *name = NULL;
    json_string_t *desc = NULL;

    do {
        channel = (json_object_t *)json_array_get(arr, i);
        if (channel == NULL)
            return;
        c_uuid = (json_string_t *)json_object_get(channel, "uuid");
        name = (json_string_t *)json_object_get(channel, "name");
        desc = (json_string_t *)json_object_get(channel, "description");
        if (c_uuid == NULL || name == NULL || desc == NULL) {
            return;
        }
        client_team_print_channels(c_uuid->value, name->value, desc->value);
        i++;
    } while (1);
}

void list_channels_response(response_t *response, request_data_t *request_data)
{
    client_t *client = (client_t *)request_data->data;
    json_array_t *arr = NULL;

    client->waiting_for_response = false;
    if (response->status == 200) {
        arr = (json_array_t *)json_array_parse(response->body);
        if (arr == NULL)
            return;
        display_channel(arr);
    }
    if (response->status == 403) {
        client_error_unauthorized();
    }
    if (response->status == 404) {
        client_error_unknown_team(client->context->team_uuid);
    }
}

void list_channels(client_t *client)
{
    request_t *request = calloc(1, sizeof(request_t));
    char *bearer = add_bearer(client->user_uuid, client->instance_id);

    if (bearer == NULL || request == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    request->route = (route_t){"GET", "/teams/channels"};
    request->body = strdup("");
    request_add_header(request, "Authorization", bearer);
    request_add_param(request, "team-uuid", client->context->team_uuid);
    api_client_send_request(client->api_handler, request,
        &list_channels_response, client);
    client->waiting_for_response = true;
}
