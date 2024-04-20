/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** send
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

void send_response(response_t *response, request_data_t *request_data)
{
    client_t *cli = (client_t *)request_data->data;
    json_object_t *jobj = NULL;
    json_string_t *uuid = NULL;

    cli->waiting_for_response = false;
    if (response->status == 200 || response->status == 204) {
        printf("CLI : Message sent\n");
    }
    if (response->status == 404) {
        jobj = (json_object_t *)json_parse(request_data->req->body);
        uuid = (json_string_t *)json_object_get(jobj, "recipient_uuid");
        if (uuid == NULL)
            return;
        client_error_unknown_user(uuid->value);
    }
    if (response->status != 200 && response->status != 204 &&
        response->status != 404) {
        printf("Error: message not sent\n");
    }
}

static void send_send(client_t *client, char *user_uuid, char *message_body)
{
    json_object_t *jobj = json_object_create("root");
    json_string_t *recipient = json_string_create("recipient_uuid", user_uuid);
    json_string_t *body = json_string_create("content", message_body);
    json_object_t *message = json_object_create("message");
    request_t *request = calloc(1, sizeof(request_t));
    char *bearer = add_bearer(client->user_uuid);

    if (jobj == NULL || request == NULL || recipient == NULL ||
        body == NULL || message == NULL || bearer == NULL)
        return;
    json_object_add(message, (json_t *)body);
    json_object_add(jobj, (json_t *)recipient);
    json_object_add(jobj, (json_t *)message);
    request->route = (route_t){"POST", "/messages/send"};
    request->body = json_serialize((json_t *)jobj);
    request_add_header(request, "Authorization", bearer);
    api_client_send_request(client->api_handler, request, &send_response,
        client);
    client->waiting_for_response = true;
}

void cmd_send(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len != 3) {
        printf("Usage: /send [\"user_uuid\"] [\"message_body\"]\n");
        return;
    }
    if (strlen(parsed_cmd[2]) < 1 || strlen(parsed_cmd[2]) > 512) {
        printf("Error: message must be between 1 and 512 characters\n");
        return;
    }
    if (uuid_from_string(parsed_cmd[1]) == NULL) {
        client_error_unknown_user(parsed_cmd[1]);
        return;
    }
    if (client->is_logged == false) {
        client_error_unauthorized();
        return;
    }
    send_send(client, parsed_cmd[1], parsed_cmd[2]);
}
