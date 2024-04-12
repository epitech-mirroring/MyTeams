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
// Route
#define ROUTE_SIZE 256
// Parameters
#define PARAMS_MAX 8
#define KEY_SIZE 64
#define VALUE_SIZE 128

typedef enum request_method_e {
    GET = 0b0001,
    POST = 0b0010,
    DELETE = 0b0011,
    PUT = 0b0100,
} request_method_t;

typedef struct route_s {
    request_method_t method;
    char path[ROUTE_SIZE];
} route_t;

typedef struct param_s {
    char key[KEY_SIZE];
    char value[VALUE_SIZE];
} param_t;

typedef struct request_header_s {
    route_t route;
    size_t content_length;
} request_header_t;

typedef struct request_s {
    request_header_t header;
    param_t params[PARAMS_MAX];
    char *body;
} request_t;

typedef unsigned int status_code_t;

typedef struct response_header_s {
    status_code_t status_code;
    size_t content_length;
} response_header_t;

typedef struct response_s {
    response_header_t header;
    char *body;
} response_t;

typedef struct host_s {
    char *ip;
    int port;
} host_t;

typedef response_t (*route_handler_t)(request_t *request);
typedef void (*network_promise_consumer_t)(response_t response);

typedef struct request_promises_s {
    request_t *request;
    network_promise_consumer_t consumer;
} request_promises_t;

typedef struct network_router_s {
    struct {
        route_t route;
        route_handler_t handler;
    } *routes;
    size_t routes_count;
} network_router_t;

typedef enum waiting_socket_mode_e {
    WRITE,
    READ
} waiting_socket_mode_t;

typedef void (*waiting_socket_consumer_t)(int socket, void *data);

typedef struct waiting_socket_s {
    int socket;
    waiting_socket_mode_t mode;
    waiting_socket_consumer_t consumer;
    void *data;
} waiting_socket_t;

typedef struct network_manager_s {
    waiting_socket_t **waiting_sockets;
    size_t waiting_sockets_count;
    fd_set read_fds;
    fd_set write_fds;
    int max_fd;
} network_manager_t;
