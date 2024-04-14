/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include "network/router.h"
#include "network/network_manager.h"

void apply_middlewares(const network_router_t *router, request_t **request)
{
    route_t req_route = (*request)->header.route;
    middlewares_t *tmp = NULL;

    for (size_t j = 0; j < router->middlewares_count; j++) {
        tmp = &router->middlewares[j];
        if (strncmp(tmp->route->path, req_route.path,
            strlen(tmp->route->path)) == 0
            && tmp->route->method == req_route.method)
            (*request) = tmp->handler((*request), tmp->data);
    }
}

bool run_route(const network_router_t *router, request_t **request,
    response_t **response)
{
    route_t req_route = (*request)->header.route;
    route_t *tmp = NULL;

    apply_middlewares(router, request);
    for (size_t i = 0; i < router->routes_count; i++) {
        tmp = router->routes[i].route;
        if (strncmp(tmp->path, req_route.path, strlen(tmp->path)) == 0
            && tmp->method == req_route.method) {
            *response = router->routes[i].handler(*request);
            return true;
        }
    }
    return false;
}

void router_handle_request(int client_socket, void *data)
{
    network_router_t *router = (network_router_t *) data;
    request_t *request = router_read_request(client_socket);
    waiting_socket_t *response_sock = malloc(sizeof(waiting_socket_t));
    response_t *response = NULL;
    bool route_found = false;

    if (!request) {
        response = create_server_error_response();
    } else {
        route_found = run_route(router, &request, &response);
        if (!route_found)
            response = create_not_found_response();
    }
    response_sock->socket = client_socket;
    response_sock->mode = WRITE;
    response_sock->consumer = &router_send_response;
    response_sock->data = response;
    network_manager_add_waiting_socket(router->manager, response_sock);
    destroy_request(request);
}

static request_header_t *receive_request_header(int client_socket)
{
    request_header_t *header = calloc(1, sizeof(request_header_t));
    char *header_buffer = calloc(1, sizeof(request_header_t));

    if (!header || !header_buffer)
        return NULL;
    if (recv(client_socket, header_buffer, sizeof(request_header_t), 0)
        != sizeof(request_header_t))
        return NULL;
    header = deserialize_request_header(header_buffer);
    free(header_buffer);
    return header;
}

static char *receive_request_content(int client_socket,
    request_header_t *header)
{
    char *content_buffer = calloc(header->content_length + sizeof(param_t)
        * PARAMS_MAX, sizeof(char));

    if (!content_buffer)
        return NULL;
    if (recv(client_socket, content_buffer, header->content_length
        + sizeof(param_t) * PARAMS_MAX, 0)
        != (ssize_t) (header->content_length + sizeof(param_t) * PARAMS_MAX))
        return NULL;
    return content_buffer;
}

request_t *router_read_request(int client_socket)
{
    request_header_t *header = receive_request_header(client_socket);
    char *content = NULL;
    request_t *request = NULL;

    if (!header)
        return NULL;
    content = receive_request_content(client_socket, header);
    if (!content)
        return NULL;
    request = deserialize_request(header, content);
    free(header);
    free(content);
    return request;
}
