/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

roundtable_server_t *create_server()
{
    roundtable_server_t *server = calloc(1, sizeof(roundtable_server_t));

    if (!server)
        return server;
    server->clients = NULL;
    server->teams = NULL;
    server->direct_messages = NULL;
    server->client_count = 0;
    server->message_count = 0;
    server->team_count = 0;
    return server;
}
