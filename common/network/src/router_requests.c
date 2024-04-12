/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "network/router.h"
#include "network/network_manager.h"

void router_handle_request(int client_socket, void *data)
{
    network_router_t *router = (network_router_t *)data;
    request_t *request = router_read_request(client_socket);
    waiting_socket_t *response_sock = malloc(sizeof(waiting_socket_t));
    response_t response;

    for (size_t i = 0; i < router->routes_count; i++) {
        if (strcmp(router->routes[i].route->path, request->header.route.path) == 0
                   && router->routes[i].route->method == request->header.route.method) {
            for (size_t j = 0; j < router->middlewares_count; j++) {
                if (strncmp(router->middlewares[j].route->path, request->header.route.path,
                            strlen(router->middlewares[j].route->path)) == 0
                            && router->middlewares[j].route->method == request->header.route.method)
                    request = router->middlewares[j].handler(request, router->middlewares[j].data);
            }
            response = router->routes[i].handler(request);
            break;
        }
    }
    response_sock->socket = client_socket;
    response_sock->mode = WRITE;
    response_sock->consumer = &router_send_response;
    response_sock->data = &response;
    network_manager_add_waiting_socket(router->manager, response_sock);
    destroy_request(request);
}

request_t *router_read_request(int client_socket)
{
    request_t *request = NULL;
    request_header_t *header = NULL;
    char *header_buffer = calloc(1, sizeof(request_header_t));
    char *content_buffer = NULL;

    if (!header_buffer)
        return NULL;
    read(client_socket, header_buffer, sizeof(request_header_t));
    header = deserialize_request_header(header_buffer);
    content_buffer = calloc(header->content_length + sizeof(param_t) * PARAMS_MAX, sizeof(char));
    if (!content_buffer)
        return NULL;
    read(client_socket, content_buffer, header->content_length + sizeof(param_t) * PARAMS_MAX);
    request = deserialize_request(header, content_buffer);
    free(header_buffer);
    return request;
}
