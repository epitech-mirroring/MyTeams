/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "network/router.h"
#include "network/manager.h"

router_t *router_init(host_t host)
{
    router_t *router = calloc(1, sizeof(router_t));

    if (router == NULL)
        return NULL;
    router->ws_manager = ws_manager_init();
    router->routes = NULL;
    router->routes_count = 0;
    router->host = host;
    return router;
}

void router_destroy(router_t *router)
{
    for (size_t i = 0; i < router->routes_count; i++) {
        free(router->routes[i].path);
    }
    free(router->routes);
    ws_manager_destroy(router->ws_manager);
    free(router);
}
