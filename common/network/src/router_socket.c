/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <netinet/in.h>
#include <stdlib.h>
#include "network/router.h"
#include "network/network_manager.h"

static int socket_accept(int server_socket)
{
    struct sockaddr_in client;
    int client_socket;
    socklen_t size = sizeof(client);

    client_socket = accept(server_socket, (struct sockaddr *)&client, &size);
    return client_socket;
}

void router_socket_accept(int server_socket, void *data)
{
    network_router_t *router = (network_router_t *)data;
    int client_socket = socket_accept(server_socket);
    waiting_socket_t *socket = malloc(sizeof(waiting_socket_t));
    waiting_socket_t *new_socket = malloc(sizeof(waiting_socket_t));

    socket->socket = client_socket;
    socket->mode = READ;
    socket->consumer = &router_handle_request;
    socket->data = router;
    network_manager_add_waiting_socket(router->manager, socket);
    new_socket->socket = server_socket;
    new_socket->mode = READ;
    new_socket->consumer = &router_socket_accept;
    new_socket->data = router;
    network_manager_add_waiting_socket(router->manager, new_socket);
}
