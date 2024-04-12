/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "network/network_manager.h"

void network_manager_handle_waiting_sockets(network_manager_t *manager)
{
    FD_ZERO(&manager->read_fds);
    FD_ZERO(&manager->write_fds);
    static struct timeval timeout = {0, 1000};
    waiting_socket_t **to_remove = calloc(1, sizeof(waiting_socket_t *));
    waiting_socket_t **tmp_to_remove = NULL;
    size_t to_remove_count = 0;
    waiting_socket_t *tmp = NULL;

    if (to_remove == NULL)
        return;
    for (size_t i = 0; i < manager->waiting_sockets_count; i++) {
        if (manager->waiting_sockets[i]->mode == READ)
            FD_SET(manager->waiting_sockets[i]->socket, &manager->read_fds);
        if (manager->waiting_sockets[i]->mode == WRITE)
            FD_SET(manager->waiting_sockets[i]->socket, &manager->write_fds);
    }
    if (select(manager->max_fd + 1, &manager->read_fds, &manager->write_fds,
               NULL, &timeout) == -1) {
        fprintf(stderr, "Select failed\n");
    }
    for (size_t i = 0; i < manager->waiting_sockets_count; i++) {
        tmp = manager->waiting_sockets[i];
        if (FD_ISSET(tmp->socket, &manager->read_fds) && tmp->mode == READ) {
            tmp_to_remove = realloc(to_remove, sizeof(waiting_socket_t *) * (to_remove_count + 2));
            if (tmp_to_remove == NULL)
                return;
            to_remove = tmp_to_remove;
            to_remove[to_remove_count] = tmp;
            to_remove[to_remove_count + 1] = NULL;
            to_remove_count++;
            tmp->consumer(tmp->socket, tmp->data);
        }
        if (FD_ISSET(tmp->socket, &manager->write_fds) && tmp->mode == WRITE) {
            tmp_to_remove = realloc(to_remove, sizeof(waiting_socket_t *) * (to_remove_count + 2));
            if (tmp_to_remove == NULL)
                return;
            to_remove = tmp_to_remove;
            to_remove[to_remove_count] = tmp;
            to_remove[to_remove_count + 1] = NULL;
            to_remove_count++;
            tmp->consumer(tmp->socket, tmp->data);
        }
    }
    for (size_t i = 0; i < to_remove_count; i++) {
        network_manager_remove_waiting_socket(manager, to_remove[i]->socket);
        free(to_remove[i]);
    }
    free(to_remove);
}

void network_manager_remove_waiting_socket(network_manager_t *manager, int socket)
{
    size_t i = 0;
    waiting_socket_t **tmp = NULL;

    while (i < manager->waiting_sockets_count) {
        if (manager->waiting_sockets[i]->socket == socket) {
            free(manager->waiting_sockets[i]);
            for (size_t j = i; j < manager->waiting_sockets_count - 1; j++) {
                manager->waiting_sockets[j] = manager->waiting_sockets[j + 1];
            }
            manager->waiting_sockets_count--;
            return;
        }
        i++;
    }
    tmp = realloc(manager->waiting_sockets, sizeof(waiting_socket_t *) * (manager->waiting_sockets_count + 1));
    if (tmp == NULL)
        return;
    manager->waiting_sockets = tmp;
}

void network_manager_add_waiting_socket(network_manager_t *manager, waiting_socket_t *socket)
{
    waiting_socket_t **tmp = NULL;

    tmp = realloc(manager->waiting_sockets, sizeof(waiting_socket_t *) * (manager->waiting_sockets_count + 2));
    if (tmp == NULL)
        return;
    manager->waiting_sockets = tmp;
    manager->waiting_sockets[manager->waiting_sockets_count] = socket;
    manager->waiting_sockets[manager->waiting_sockets_count + 1] = NULL;
    manager->waiting_sockets_count++;
    if (socket->socket > manager->max_fd)
        manager->max_fd = socket->socket;
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

    if (sock == -1) {
        fprintf(stderr, "Failed to create socket\n");
        return 0;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(host->port);
    addr.sin_addr.s_addr = inet_addr(host->ip);
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "Failed to connect to %s:%d\n", host->ip, host->port);
        return 0;
    }
    return sock;
}

int socket_create_server(host_t *host)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    int opt = 1;

    if (sock == -1) {
        fprintf(stderr, "Failed to create socket\n");
        return 0;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(host->port);
    addr.sin_addr.s_addr = inet_addr(host->ip);
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        fprintf(stderr, "Failed to set socket options\n");
        return 0;
    }
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "Failed to bind to %s:%d\n", host->ip, host->port);
        return 0;
    }
    if (listen(sock, 10) == -1) {
        fprintf(stderr, "Failed to listen on %s:%d\n", host->ip, host->port);
        return 0;
    }
    return sock;
}



char *serialize_route(route_t route)
{
    char *str = malloc(sizeof(route_t) + 1);
    char path[ROUTE_SIZE];

    if (str == NULL)
        return NULL;
    for (size_t i = 0; i < ROUTE_SIZE; i++) {
        path[i] = route.path[i];
    }
    strcpy(str, serialize_request_method(route.method));
    for (size_t i = 0; i < ROUTE_SIZE; i++) {
        str[i + 4] = route.path[i];
    }
    return str;
}

char *serialize_param(param_t param)
{
    char *key = calloc(sizeof(char), sizeof(param.key) * KEY_SIZE + 1);
    char *value = calloc(sizeof(char), sizeof(param.value) * VALUE_SIZE + 1);
    char *param_str = calloc(sizeof(char), sizeof(param_t) + 1);

    if (key == NULL || value == NULL || param_str == NULL)
        return NULL;
    for (size_t i = 0; i < KEY_SIZE; i++) {
        key[i] = param.key[i];
    }
    for (size_t i = 0; i < VALUE_SIZE; i++) {
        value[i] = param.value[i];
    }
    sprintf(param_str, "%s%s", key, value);
    free(key);
    free(value);
    return param_str;
}

char *serialize_params(param_t params[PARAMS_MAX])
{
    char *buff = calloc(sizeof(char), (sizeof(param_t) * PARAMS_MAX) + 1);
    if (buff == NULL)
        return NULL;

    for (size_t i = 0; i < PARAMS_MAX; i++) {
        if (params[i].key[0] == '\0')
            break;
        sprintf(buff, "%s%s", buff, serialize_param(params[i]));
    }
    return buff;
}

char *serialize_request_method(request_method_t method)
{
    char *str = malloc(4);

    sprintf(str, "%c%c%c%c", method & 0xFF, (method >> 8) & 0xFF, (method >> 16) & 0xFF, (method >> 24) & 0xFF);
    return str;
}

char *serialize_size_t(size_t size)
{
    char *str = malloc(sizeof(size_t) + 1);

    if (str == NULL)
        return NULL;
    sprintf(str, "%c%c%c%c%c%c%c%c", (char)(size & 0xFF), (char)(size >> 8) & 0xFF, (char)(size >> 16) & 0xFF, (char)(size >> 24) & 0xFF,
            (char)(size >> 32) & 0xFF, (char)(size >> 40) & 0xFF, (char)(size >> 48) & 0xFF, (char)(size >> 56) & 0xFF);
    return str;
}

char *serialize_request_header(request_header_t header)
{
    char *str = malloc(sizeof(request_header_t) + 1);

    if (str == NULL)
        return NULL;
    sprintf(str, "%s%s", serialize_route(header.route), serialize_size_t(header.content_length));
    return str;
}

char *serialize_request(request_t *request)
{
    char *str = malloc(sizeof(request_t) + 1);

    if (str == NULL)
        return NULL;
    sprintf(str, "%s%s%s", serialize_request_header(request->header), serialize_params(request->params), request->body);
    return str;
}