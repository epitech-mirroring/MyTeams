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

void network_router_add_middleware(network_router_t *router, middlewares_t *middleware)
{
    middlewares_t *middlewares_tmp = NULL;

    middlewares_tmp = realloc(router->middlewares, sizeof(middlewares_t) * (router->middlewares_count + 1));
    if (!middlewares_tmp)
        return;
    router->middlewares_count++;
    router->middlewares = middlewares_tmp;
    router->middlewares[router->middlewares_count - 1].route = middleware->route;
    router->middlewares[router->middlewares_count - 1].handler = middleware->handler;
    router->middlewares[router->middlewares_count - 1].data = middleware->data;
}

void network_router_remove_middleware(network_router_t *router, middlewares_t *middleware)
{
    middlewares_t *middlewares_tmp = NULL;

    for (size_t i = 0; i < router->middlewares_count; i++) {
        if (strcmp(router->middlewares[i].route->path,
                   middleware->route->path) == 0 && router->middlewares[i].route->method == middleware->route->method) {
            for (size_t j = i; j < router->middlewares_count - 1; j++) {
                router->middlewares[j] = router->middlewares[j + 1];
            }
            middlewares_tmp = realloc(router->middlewares,
                                      sizeof(middlewares_t) * (router->middlewares_count - 1));
            if (!middlewares_tmp)
                return;
            router->middlewares_count--;
            router->middlewares = middlewares_tmp;
            break;
        }
    }
}
