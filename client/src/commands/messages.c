/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** messages
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

void display_messages(json_array_t *arr)
{
    int i = 0;
    json_object_t *message = NULL;
    json_string_t *sender = NULL;
    json_string_t *body = NULL;
    json_number_t *timestamp = NULL;

    do {
        message = (json_object_t *)json_array_get(arr, i);
        if (message == NULL)
            return;
        sender = (json_string_t *)json_object_get(message, "sender_uuid");
        body = (json_string_t *)json_object_get(message, "content");
        timestamp = (json_number_t *)json_object_get(message, "timestamp");
        if (sender == NULL || body == NULL || timestamp == NULL) {
            return;
        }
        client_private_message_print_messages(sender->value, timestamp->value,
            body->value);
        i++;
    } while (1);
}

void messages_response(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;
    json_array_t *arr = NULL;

    cli->waiting_for_response = false;
    if (response->status == 200) {
        arr = (json_array_t *)json_array_parse(response->body);
        if (arr == NULL)
            return;
        display_messages(arr);
    }
    if (response->status == 404) {
        client_error_unknown_user(
            request_get_param(request_data->req, "uuid"));
    }
}

static void send_messages(client_t *client, char *user_uuid)
{
    char *bearer = add_bearer(client->user_uuid);
    request_t *request = calloc(1, sizeof(request_t));

    if (bearer == NULL || request == NULL)
        return;
    request->route = (route_t){"GET", "/messages"};
    request_add_param(request, "uuid", user_uuid);
    request_add_header(request, "Authorization", bearer);
    request->body = strdup("");
    api_client_send_request(client->api_handler, request, &messages_response,
        client);
    client->waiting_for_response = true;
}

void messages(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len != 2) {
        printf("Usage: /messages [\"user_uuid\"]\n");
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
    send_messages(client, parsed_cmd[1]);
}
