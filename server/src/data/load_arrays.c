/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <string.h>
#include "server_data.h"
#include "server.h"

void deserialize_clients(roundtable_server_t *server, json_array_t *clients)
{
    for (size_t i = 0; i < clients->size; i++) {
        deserialize_client(server,
            (json_object_t *) json_array_get(clients, i));
    }
}

void deserialize_client(roundtable_server_t *server, json_object_t *client)
{
    roundtable_client_t *new_client = calloc(1, sizeof(roundtable_client_t));
    json_string_t *uuid = NULL;
    json_string_t *username = NULL;

    if (new_client == NULL)
        return;
    uuid = (json_string_t *) json_object_get(client, "uuid");
    username = (json_string_t *) json_object_get(client, "username");
    COPY_UUID(new_client->uuid, uuid->value);
    new_client->username = strdup(username->value);
    new_client->status = OFFLINE;
    roundtable_server_add_client(server, new_client);
}

void deserialize_teams(roundtable_server_t *server, json_array_t *teams)
{
    for (size_t i = 0; i < teams->size; i++) {
        deserialize_team(server, (json_object_t *) json_array_get(teams, i));
    }
}

void deserialize_subscribers(roundtable_server_t *server,
    json_array_t *subscribers, roundtable_team_t *team)
{
    json_string_t *uuid = NULL;
    roundtable_client_t *client = NULL;
    uuid_t uuid_struct;

    for (size_t i = 0; i < subscribers->size; i++) {
        uuid = (json_string_t *) json_array_get(subscribers, i);
        COPY_UUID(uuid_struct, uuid->value);
        client = roundtable_server_get_client_by_uuid(server, uuid_struct);
        if (client != NULL)
            roundtable_team_add_subscriber(team, client);
    }
}

void deserialize_messages(json_array_t *messages, roundtable_thread_t *thread)
{
    for (size_t i = 0; i < messages->size; i++) {
        deserialize_message(
            (json_object_t *) json_array_get(messages, i), thread);
    }
}
