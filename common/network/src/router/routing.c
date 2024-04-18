/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include "network/router.h"

route_handler_t *router_get_route(router_t *router, const char *path)
{
    for (size_t i = 0; i < router->routes_count; i++) {
        if (strcmp(router->routes[i].path, path) == 0)
            return &router->routes[i];
    }
    return NULL;
}
