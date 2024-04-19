/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

void roundtable_server_add_client(roundtable_server_t *server,
    roundtable_client_t *client)
{
    roundtable_client_t **new_clients = NULL;

    new_clients = realloc(server->clients,
        sizeof(roundtable_client_t *) * (server->client_count + 1));
    if (new_clients == NULL)
        return;
    server->clients = new_clients;
    server->clients[server->client_count] = client;
    server->client_count++;
}
