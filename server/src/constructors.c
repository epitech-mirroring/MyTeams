/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "../include/server.h"
#include "network/router.h"

roundtable_server_t *create_server(int port)
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
    server->router = router_init((host_t){.ip = "127.0.0.1", .port = port});
    return server;
}
