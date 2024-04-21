/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "../include/server.h"

roundtable_server_t *create_server(int port)
{
    roundtable_server_t *server = calloc(1, sizeof(roundtable_server_t));
    host_t host;

    if (!server)
        return server;
    server->clients = NULL;
    server->teams = NULL;
    server->direct_messages = NULL;
    server->client_count = 0;
    server->message_count = 0;
    server->team_count = 0;
    host.ip = "127.0.0.1";
    host.port = port;
    server->instance_count = 0;
    server->instances = calloc(1, sizeof(roundtable_client_instance_t *));
    server->router = router_init(host);
    return server;
}
