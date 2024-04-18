/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <stddef.h>
#include <sys/select.h>
#include <stdbool.h>
// Communication
#define BUFFER_SIZE 104857600
#ifndef _SSIZE_T
typedef long ssize_t;
#endif

typedef struct route_s {
    char method[8];
    char path[128];
} route_t;

typedef struct header_s {
    char *key;
    char *value;
} header_t;

typedef struct param_s {
    char *key;
    char *value;
} param_t;

typedef struct request_s {
    route_t route;
    header_t *headers;
    size_t headers_count;
    param_t *params;
    size_t params_count;
    char *body;
} request_t;

typedef struct response_s {
    int status;
    char *status_message;
    header_t *headers;
    size_t headers_count;
    char *body;
} response_t;

typedef struct host_s {
    char *ip;
    int port;
} host_t;

typedef enum waiting_socket_mode_e {
    READ,
    WRITE
} waiting_socket_mode_t;

typedef struct waiting_socket_s {
    int socket;
    waiting_socket_mode_t mode;
    bool (*callback)(struct waiting_socket_s *socket);
    void *data;
} waiting_socket_t;

typedef struct waiting_sockets_s {
    fd_set read_fds;
    fd_set write_fds;
    waiting_socket_t *sockets;
    size_t sockets_count;
    int max_fd;
} waiting_sockets_t;

typedef struct ws_manager_s {
    waiting_sockets_t *ws;
    bool running;
} ws_manager_t;
