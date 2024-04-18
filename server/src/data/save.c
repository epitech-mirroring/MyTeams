/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server_data.h"

void save_data(roundtable_server_t *server, const char *path)
{
    json_object_t *json = json_object_create("root");

    json_object_add(json, (json_t *) serialize_clients(server));
    json_object_add(json, (json_t *) serialize_teams(server));
    json_object_add(json, (json_t *) serialize_direct_messages(server));
    json_save_to_file((json_t *) json, path);
    json_destroy((json_t *) json);
}

json_array_t *serialize_clients(roundtable_server_t *server)
{
    json_array_t *clients = json_array_create("clients");

    for (size_t i = 0; i < server->client_count; i++) {
        json_array_add(clients,
            (json_t *) serialize_client(server->clients[i]));
    }
    return clients;
}

json_array_t *serialize_teams(roundtable_server_t *server)
{
    json_array_t *teams = json_array_create("teams");

    for (size_t i = 0; i < server->team_count; i++) {
        json_array_add(teams, (json_t *) serialize_team(server->teams[i]));
    }
    return teams;
}

json_array_t *serialize_direct_messages(roundtable_server_t *server)
{
    json_array_t *direct_messages = json_array_create("direct_messages");

    for (size_t i = 0; i < server->message_count; i++) {
        json_array_add(direct_messages,
            (json_t *) serialize_direct_message(server->direct_messages[i]));
    }
    return direct_messages;
}
