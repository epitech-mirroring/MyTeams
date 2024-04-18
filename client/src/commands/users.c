/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** users
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

void display_users(json_array_t *arr)
{
    int i = 0;
    json_object_t *user = NULL;
    json_string_t *uuid = NULL;
    json_string_t *username = NULL;
    json_string_t *status = NULL;

    do {
        user = (json_object_t *) json_array_get(arr, i);
        if (user == NULL)
            return;
        uuid = (json_string_t *) json_object_get(user, "uuid");
        username = (json_string_t *) json_object_get(user, "name");
        status = (json_string_t *) json_object_get(user, "status");
        if (uuid == NULL || username == NULL || status == NULL) {
            return;
        }
        client_print_users(uuid->value, username->value,
            (status->value[1] == 'N' ? 1 : 0));
        i++;
    } while (1);
}

void users_response(response_t *response, request_data_t *request_data)
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
}

static void send_users(client_t *client)
{
    json_object_t *jobj = json_object_create("root");
    json_string_t *uuid = json_string_create("user_uuid", client->user_uuid);
    request_t *request = calloc(1, sizeof(request_t));

    if (jobj == NULL || uuid == NULL || request == NULL) {
        printf("Error: malloc failed\n");
        return;
    }
    json_object_add(jobj, (json_t *)uuid);
    request->route = (route_t){"GET", "/users"};
    request->body = json_serialize((json_t *)jobj);
    api_client_send_request(client->api_handler, request, &users_response,
        client);
    client->waiting_for_response = true;
}

void users(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len != 1) {
        printf("Usage: /users\n");
        return;
    }
    if (client->is_logged == false) {
        client_error_unauthorized();
        return;
    }
    send_users(client);
}
