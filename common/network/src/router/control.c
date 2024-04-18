/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <netinet/in.h>
#include <stdio.h>
#include "network/router.h"
#include "network/sockets.h"
#include "network/manager.h"

void router_start(router_t *router)
{
    int server_socket = socket_create_server(router->host);
    waiting_socket_t *server_ws = NULL;

    if (server_socket == -1)
        return;
    server_ws = waiting_sockets_add_socket(router->ws_manager->ws,
        server_socket, READ, &router_accept_connection);
    if (server_ws == NULL)
        return;
    server_ws->data = router;
    ws_manager_start(router->ws_manager);
}

static int socket_accept(int server_socket)
{
    struct sockaddr_in client;
    int client_socket;
    socklen_t size = sizeof(client);

    client_socket = accept(server_socket, (struct sockaddr *)&client, &size);
    return client_socket;
}

bool router_accept_connection(waiting_socket_t *socket)
{
    router_t *router = socket->data;
    int client_socket = socket_accept(socket->socket);
    waiting_socket_t *client_ws = NULL;

    if (client_socket == -1)
        return false;
    client_ws = waiting_sockets_add_socket(router->ws_manager->ws,
        client_socket, READ, &router_handle_request);
    client_ws->data = router;
    return true;
}
