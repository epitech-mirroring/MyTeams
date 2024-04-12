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

void network_router_add_route(network_router_t *router, route_t route, route_handler_t handler)
{
    routes_binding_t *routes_tmp = NULL;

    routes_tmp = realloc(router->routes, sizeof(route_handler_t) * (router->routes_count + 1));
    if (!routes_tmp)
        return;
    router->routes_count++;
    router->routes = routes_tmp;
    router->routes[router->routes_count - 1].route = calloc(1, sizeof(route_t));
    router->routes[router->routes_count - 1].route->method = route.method;
    strcpy(router->routes[router->routes_count - 1].route->path, route.path);
    router->routes[router->routes_count - 1].handler = handler;
}

void network_router_remove_route(network_router_t *router, route_t route)
{
    routes_binding_t *routes_tmp = NULL;

    for (size_t i = 0; i < router->routes_count; i++) {
        if (strcmp(router->routes[i].route->path, route.path) == 0 && router->routes[i].route->method == route.method) {
            free(router->routes[i].route);
            for (size_t j = i; j < router->routes_count - 1; j++) {
                router->routes[j] = router->routes[j + 1];
            }
            routes_tmp = realloc(router->routes, sizeof(route_handler_t) * (router->routes_count - 1));
            if (!routes_tmp)
                return;
            router->routes = routes_tmp;
            router->routes_count--;
            break;
        }
    }
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
