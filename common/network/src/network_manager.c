/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "network/network_manager.h"

void call_set_sockets(const network_manager_t *manager,
    waiting_socket_t ***called, size_t *called_count)
{
    waiting_socket_t *tmp = NULL;
    waiting_socket_t **tmp_called = NULL;
    fd_set set;

    for (size_t i = 0; i < manager->waiting_sockets_count; i++) {
        tmp = manager->waiting_sockets[i];
        set = tmp->mode == READ ? manager->read_fds : manager->write_fds;
        if (FD_ISSET(tmp->socket, &set)) {
            tmp_called = realloc((*called), sizeof(waiting_socket_t *) * (
                (*called_count) + 2));
            (*called) = tmp_called;
            (*called)[(*called_count)] = tmp;
            (*called)[(*called_count) + 1] = NULL;
            (*called_count)++;
        }
    }
}

void network_manager_reset_fds(network_manager_t *manager)
{
    FD_ZERO(&manager->read_fds);
    FD_ZERO(&manager->write_fds);
    for (size_t i = 0; i < manager->waiting_sockets_count; i++) {
        FD_SET(manager->waiting_sockets[i]->socket,
            manager->waiting_sockets[i]->mode == READ ?
            &manager->read_fds : &manager->write_fds);
    }
}

void network_manager_handle_waiting_sockets(network_manager_t *manager)
{
    waiting_socket_t **called = calloc(1, sizeof(waiting_socket_t *));
    size_t to_remove_count = 0;

    if (called == NULL)
        return;
    network_manager_reset_fds(manager);
    select(manager->max_fd + 1, &manager->read_fds, &manager->write_fds,
        NULL, NULL);
    call_set_sockets(manager, &called, &to_remove_count);
    for (size_t i = 0; i < to_remove_count; i++) {
        called[i]->consumer(called[i]->socket, called[i]->data);
        network_manager_remove_waiting_socket(manager, called[i]->socket,
            called[i]->mode);
    }
    free(called);
}

ssize_t network_manager_find_waiting_socket(network_manager_t *manager,
    int socket, waiting_socket_mode_t mode)
{
    ssize_t i = 0;

    while (i < (ssize_t) manager->waiting_sockets_count) {
        if (manager->waiting_sockets[i]->socket == socket &&
        manager->waiting_sockets[i]->mode == mode)
            return i;
        i++;
    }
    return -1;
}

void network_manager_remove_waiting_socket(network_manager_t *manager,
    int socket, waiting_socket_mode_t mode)
{
    ssize_t index = network_manager_find_waiting_socket(manager, socket, mode);
    waiting_socket_t **tmp = NULL;

    if (index == -1)
        return;
    free(manager->waiting_sockets[index]);
    for (size_t i = index; i < manager->waiting_sockets_count - 1; i++)
        manager->waiting_sockets[i] = manager->waiting_sockets[i + 1];
    tmp = realloc(manager->waiting_sockets, sizeof(waiting_socket_t *) *
        manager->waiting_sockets_count);
    if (tmp == NULL)
        return;
    manager->waiting_sockets = tmp;
    manager->waiting_sockets_count--;
}

void network_manager_add_waiting_socket(network_manager_t *manager,
    waiting_socket_t *socket)
{
    waiting_socket_t **tmp = NULL;

    tmp = realloc(manager->waiting_sockets, sizeof(waiting_socket_t *) *
        (manager->waiting_sockets_count + 2));
    if (tmp == NULL)
        return;
    manager->waiting_sockets = tmp;
    manager->waiting_sockets[manager->waiting_sockets_count] = socket;
    manager->waiting_sockets[manager->waiting_sockets_count + 1] = NULL;
    manager->waiting_sockets_count++;
    manager->max_fd = socket->socket > manager->max_fd ?
        socket->socket : manager->max_fd;
}

network_manager_t *network_manager_create(void)
{
    network_manager_t *new = malloc(sizeof(network_manager_t));

    if (new == NULL)
        return NULL;
    new->waiting_sockets = NULL;
    new->waiting_sockets_count = 0;
    new->max_fd = 0;
    return new;
}

void network_manager_destroy(network_manager_t *manager)
{
    for (size_t i = 0; i < manager->waiting_sockets_count; i++) {
        free(manager->waiting_sockets[i]);
    }
    free(manager->waiting_sockets);
    free(manager);
}

int socket_create_client(host_t *host)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;

    if (sock == -1)
        return 0;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(host->port);
    addr.sin_addr.s_addr = inet_addr(host->ip);
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        return 0;
    return sock;
}

int socket_create_server(host_t *host)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    int opt = 1;

    if (sock == -1)
        return 0;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(host->port);
    addr.sin_addr.s_addr = inet_addr(host->ip);
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1 ||
    bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1 ||
    listen(sock, 10) == -1)
        return 0;
    return sock;
}

char *serialize_request(request_t *request)
{
    char *str = calloc(sizeof(request_header_t) + sizeof(param_t) * PARAMS_MAX
        + request->header.content_length, sizeof(char));

    if (str == NULL)
        return NULL;
    memcpy(str, &request->header, sizeof(request_header_t));
    memcpy(str + sizeof(request_header_t), request->params,
        sizeof(param_t) * PARAMS_MAX);
    memcpy(str + sizeof(request_header_t) + sizeof(param_t) * PARAMS_MAX,
        request->body, request->header.content_length);
    return str;
}

request_header_t *deserialize_request_header(char *str)
{
    request_header_t *header = calloc(1, sizeof(request_header_t));

    if (header == NULL)
        return NULL;
    memcpy(header, str, sizeof(request_header_t));
    return header;
}

request_t *deserialize_request(request_header_t *header,
    char *body_with_params)
{
    request_t *request = calloc(1, sizeof(request_t));

    if (request == NULL)
        return NULL;
    request->header = *header;
    memcpy(request->params, body_with_params, sizeof(param_t) * PARAMS_MAX);
    request->body = body_with_params + sizeof(param_t) * PARAMS_MAX;
    free(header);
    return request;
}

char *serialize_response(response_t *response)
{
    char *str = calloc(sizeof(response_header_t) +
        response->header.content_length, sizeof(char));

    if (str == NULL)
        return NULL;
    memcpy(str, &response->header, sizeof(response_header_t));
    memcpy(str + sizeof(response_header_t), response->body,
        response->header.content_length);
    return str;
}

response_header_t *deserialize_response_header(char *str)
{
    response_header_t *header = calloc(1, sizeof(response_header_t));

    if (header == NULL)
        return NULL;
    memcpy(header, str, sizeof(response_header_t));
    return header;
}

response_t *deserialize_response(response_header_t *header, char *response_str)
{
    response_t *response = calloc(1, sizeof(response_t));

    if (response == NULL)
        return NULL;
    response->header = *header;
    response->body = response_str;
    free(header);
    return response;
}

void destroy_request(request_t *request)
{
    free(request);
}
