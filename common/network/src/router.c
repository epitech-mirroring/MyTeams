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

void network_router_add_route(network_router_t *router, route_t route,
    route_handler_t handler)
{
    routes_binding_t *routes_tmp = NULL;

    routes_tmp = realloc(router->routes, sizeof(routes_binding_t) *
        (router->routes_count + 1));
    if (!routes_tmp)
        return;
    router->routes_count++;
    router->routes = routes_tmp;
    router->routes[router->routes_count - 1].route =
        calloc(1, sizeof(route_t));
    router->routes[router->routes_count - 1].route->method = route.method;
    strcpy(router->routes[router->routes_count - 1].route->path, route.path);
    router->routes[router->routes_count - 1].handler = handler;
}

ssize_t router_find_route(network_router_t *router, route_t route)
{
    route_t *route_tmp = NULL;

    for (ssize_t i = 0; i < (ssize_t) router->routes_count; i++) {
        route_tmp = router->routes[i].route;
        if (strcmp(route_tmp->path, route.path) == 0
            && route_tmp->method == route.method)
            return i;
    }
    return -1;
}

void network_router_remove_route(network_router_t *router, route_t route)
{
    routes_binding_t *routes_tmp = NULL;
    ssize_t index = router_find_route(router, route);

    if (index == -1)
        return;
    free(router->routes[index].route);
    for (size_t i = index; i < router->routes_count - 1; i++) {
        router->routes[i] = router->routes[i + 1];
    }
    routes_tmp = realloc(router->routes, sizeof(routes_binding_t) *
        (router->routes_count - 1));
    if (!routes_tmp)
        return;
    router->routes_count--;
    router->routes = routes_tmp;
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
