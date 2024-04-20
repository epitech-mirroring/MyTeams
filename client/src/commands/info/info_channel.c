/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** info_channel
*/

#include "myclient.h"
#include "logging_client.h"

static void channel_info_response_success(response_t *response)
{
    json_array_t *jarray = (json_array_t *)json_parse(response->body);
    json_object_t *jobj = (json_object_t *)json_array_get(jarray, 0);
    json_string_t *channel_uuid = (json_string_t *)json_object_get(jobj,
        "uuid");
    json_string_t *channel_name = (json_string_t *)json_object_get(jobj,
        "name");
    json_string_t *channel_desc = (json_string_t *)json_object_get(jobj,
        "description");

    if (channel_uuid == NULL || channel_name == NULL || channel_desc == NULL)
        return;
    client_print_channel(channel_uuid->value, channel_name->value,
        channel_desc->value);
}

static void channel_info_response_error(response_t *response,
    request_data_t *request_data)
{
    json_object_t *jobj = (json_object_t *)json_parse(response->body);
    json_string_t *error = (json_string_t *)json_object_get(jobj,
        "error_name");
    char *team_uuid = request_get_param(request_data->req, "team-uuid");
    char *channel_uuid = request_get_param(request_data->req, "channel-uuid");

    if (error == NULL || team_uuid == NULL || channel_uuid == NULL)
        return;
    if (strstr(error->value, "Team") != NULL)
        client_error_unknown_team(team_uuid);
    if (strstr(error->value, "Channel") != NULL)
        client_error_unknown_channel(channel_uuid);
}

void channel_info_response(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;

    cli->waiting_for_response = false;
    if (response->status == 200) {
        channel_info_response_success(response);
    }
    if (response->status == 404) {
        channel_info_response_error(response, request_data);
    }
    if (response->status == 403) {
        client_error_unauthorized();
    }
}

void info_channel(client_t *client)
{
    request_t *request = calloc(1, sizeof(request_t));
    char *bearer = add_bearer(client->user_uuid);

    if (bearer == NULL || request == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    request->route = (route_t){"GET", "/teams/channels"};
    request->body = strdup("");
    request_add_header(request, "Authorization", bearer);
    request_add_param(request, "team-uuid", client->context->team_uuid);
    request_add_param(request, "channel-uuid", client->context->channel_uuid);
    api_client_send_request(client->api_handler, request,
        &channel_info_response, client);
    client->waiting_for_response = true;
}
