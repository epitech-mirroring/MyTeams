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

network_router_t *router_global = NULL;

response_t *router_handle_test(request_t *request)
{
    response_t *response = calloc(1, sizeof(response_t));
    char *body = "{\"message\": \"Hello, World!\"}";

    response->header.status_code = 200;
    response->header.content_length = strlen(body);
    response->body = body;
    return response;
}

response_t *router_handle_stop(request_t *request)
{
    response_t *response = calloc(1, sizeof(response_t));
    char *body = "{\"message\": \"Goodbye, World!\"}";

    response->header.status_code = 200;
    response->header.content_length = strlen(body);
    response->body = body;
    return response;
}

int main(void)
{
    host_t *host = malloc(sizeof(host_t));
    network_router_t *router = NULL;

    if (!host)
        return 84;
    host->port = 8080;
    host->ip = "127.0.0.1";
    router = network_router_create(*host);
    if (!router) {
        free(host);
        return 84;
    }
    router_global = router;
    network_router_add_route(router, (route_t) {GET, "/api/v1/test"}, &router_handle_test);
    network_router_add_route(router, (route_t) {POST, "/api/v1/stop"}, &router_handle_stop);
    network_router_listen(router);
    network_router_destroy(router);
    free(host);
    return 0;
}
