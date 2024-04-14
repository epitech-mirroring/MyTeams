/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <string.h>
#include "network/router.h"

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
