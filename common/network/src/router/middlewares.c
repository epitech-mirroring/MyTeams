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

void router_add_middleware(router_t *router, const char *path,
    response_t *(*handler)(request_t *req, void *data), void *data)
{
    middleware_t *new_middlewares = NULL;

    new_middlewares = realloc(router->middlewares,
        sizeof(middleware_t) * (router->middlewares_count + 1));
    if (new_middlewares == NULL)
        return;
    router->middlewares = new_middlewares;
    router->middlewares[router->middlewares_count].path = strdup(path);
    router->middlewares[router->middlewares_count].handler = handler;
    router->middlewares[router->middlewares_count].data = data;
    router->middlewares_count++;
}

middleware_t **router_get_middlewares(router_t *router, const char *path)
{
    middleware_t **middlewares = calloc(router->middlewares_count + 1,
        sizeof(middleware_t *));
    size_t j = 0;

    if (middlewares == NULL)
        return NULL;
    for (size_t i = 0; i < router->middlewares_count; i++) {
        if (strncmp(router->middlewares[i].path, path,
            strlen(router->middlewares[i].path)) == 0) {
            middlewares[j] = &router->middlewares[i];
            j++;
        }
    }
    return middlewares;
}
