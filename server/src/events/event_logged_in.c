/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"

void roundtable_event_logged_in(roundtable_server_t *server,
    roundtable_client_t *client)
{
    json_object_t *data = NULL;

    for (size_t i = 0; i < server->client_count; i++) {
        data = json_object_create(NULL);
        json_object_add(data, (json_t *) json_string_create("user_uuid",
            uuid_to_string(client->uuid)));
        json_object_add(data, (json_t *) json_string_create("username",
            client->username));
        roundtable_server_send_event(server, server->clients[i],
            roundtable_server_create_event(LOGGED_IN, data));
    }
}
