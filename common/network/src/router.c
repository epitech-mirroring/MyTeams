/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "network/router.h"
#include "network/network_manager.h"
#include <stdlib.h>
#include <string.h>

network_router_t *network_router_create(host_t host)
{
    network_router_t *router = malloc(sizeof(network_router_t));

    if (!router)
        return NULL;
    router->middlewares = NULL;
    router->middlewares_count = 0;
    router->is_listening = true;
    router->server_socket = socket_create_server(&host);
    router->routes = NULL;
    router->host = host;
    router->routes_count = 0;
    router->manager = network_manager_create();
    return router;
}

void network_router_destroy(network_router_t *router)
{
    network_manager_destroy(router->manager);
    for (size_t i = 0; i < router->routes_count; i++) {
        free(router->routes[i].route);
    }
    free(router->routes);
    free(router);
}

void network_router_listen(network_router_t *router)
{
    waiting_socket_t *socket = malloc(sizeof(waiting_socket_t));

    socket->socket = router->server_socket;
    socket->mode = READ;
    socket->consumer = &router_socket_accept;
    socket->data = router;
    network_manager_add_waiting_socket(router->manager, socket);
    while (router->is_listening) {
        network_manager_handle_waiting_sockets(router->manager);
    }
}
