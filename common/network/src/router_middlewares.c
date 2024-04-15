/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/


#include <stdlib.h>
#include <string.h>
#include "network/router.h"

void network_router_add_middleware(network_router_t *router,
    middlewares_t middleware)
{
    middlewares_t *middlewares_tmp = NULL;

    middlewares_tmp = realloc(router->middlewares, sizeof(middlewares_t) *
        (router->middlewares_count + 1));
    if (!middlewares_tmp)
        return;
    router->middlewares_count++;
    router->middlewares = middlewares_tmp;
    router->middlewares[router->middlewares_count - 1].route =
        middleware.route;
    router->middlewares[router->middlewares_count - 1].handler =
        middleware.handler;
    router->middlewares[router->middlewares_count - 1].data = middleware.data;
}

ssize_t router_find_middleware(network_router_t *router, route_t route)
{
    middlewares_t *middlewares_tmp = NULL;

    for (ssize_t i = 0; i < (ssize_t) router->middlewares_count; i++) {
        middlewares_tmp = &router->middlewares[i];
        if (strcmp(middlewares_tmp->route->path, route.path) == 0 &&
            middlewares_tmp->route->method == route.method) {
            return i;
        }
    }
    return -1;
}

void network_router_remove_middleware(network_router_t *router, route_t route)
{
    middlewares_t *middlewares_tmp = NULL;
    ssize_t index = router_find_middleware(router, route);

    if (index == -1)
        return;
    middlewares_tmp = realloc(router->middlewares, sizeof(middlewares_t) *
        (router->middlewares_count - 1));
    if (!middlewares_tmp)
        return;
    router->middlewares_count--;
    router->middlewares = middlewares_tmp;
    for (size_t i = index; i < router->middlewares_count; i++) {
        router->middlewares[i] = router->middlewares[i + 1];
    }
}
