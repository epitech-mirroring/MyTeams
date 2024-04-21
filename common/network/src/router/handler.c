/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include "network/router.h"
#include "network/dto.h"

static response_t get_route_not_found_response(void)
{
    response_t res;

    res.status = 404;
    res.status_message = strdup("Not Found");
    res.body = strdup("Route not found");
    res.headers_count = 0;
    res.headers = NULL;
    res.body = strdup("");
    return res;
}

static response_t get_response(router_t *router, char *buffer, request_t *req)
{
    route_handler_t *handler = NULL;
    middleware_t **middlewares = NULL;
    response_t *res = NULL;

    req = deserialize_request(buffer);
    handler = router_get_route(router, req->route.path);
    middlewares = router_get_middlewares(router, req->route.path);
    if (handler == NULL) {
        return get_route_not_found_response();
    } else {
        for (size_t i = 0; middlewares[i] != NULL; i++) {
            res = middlewares[i]->handler(req, middlewares[i]->data);
        }
        if (res == NULL) {
            res = calloc(1, sizeof(response_t));
            *res = handler->handler(req, handler->data);
        }
    }
    free(middlewares);
    return *res;
}

bool router_handle_request(waiting_socket_t *socket)
{
    router_t *router = socket->data;
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));
    request_t *req = calloc(1, sizeof(request_t));
    response_t res = {0};

    if (req == NULL || buffer == NULL ||
        recv(socket->socket, buffer, BUFFER_SIZE, 0) <= 0) {
        free(buffer);
        free(req);
        return false;
    }
    res = get_response(router, buffer, req);
    socket->mode = WRITE;
    socket->data = serialize_response(res);
    socket->callback = &waiting_socket_send_response;
    destroy_request(req);
    free(buffer);
    destroy_response(&res);
    return true;
}

bool waiting_socket_send_response(waiting_socket_t *socket)
{
    char *res = socket->data;

    send(socket->socket, res, strlen(res), 0);
    free(res);
    return false;
}
