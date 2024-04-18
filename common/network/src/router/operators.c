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

void router_add_route(router_t *router, const char *path,
    response_t (*handler)(request_t *req, void *data), void *data)
{
    route_handler_t *new_routes = NULL;

    new_routes = realloc(router->routes,
        sizeof(route_handler_t) * (router->routes_count + 1));
    if (new_routes == NULL)
        return;
    router->routes = new_routes;
    router->routes[router->routes_count].path = strdup(path);
    router->routes[router->routes_count].handler = handler;
    router->routes[router->routes_count].data = data;
    router->routes_count++;
}
