/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once

typedef enum request_method_e {
    GET = 0b0001,
    POST = 0b0010,
    DELETE = 0b0011,
    PUT = 0b0100,
} request_method_t;

typedef struct route_s {
    request_method_t method;
    char path[256];
} route_t;

typedef struct param_s {
    char key[64];
    char value[128];
} param_t;

typedef struct request_s {
    struct {
        route_t route;
        size_t content_length;
    } header;
    param_t params[8];
    char *body;
} request_t;

typedef struct response_s {
    struct {
        unsigned int status_code;
        size_t content_length;
    } header;
    char *body;
} response_t;

typedef struct host_s {
    char *ip;
    int port;
} host_t;

typedef response_t (*route_handler_t)(request_t *request);
typedef void (*network_promise_consumer_t)(response_t response);

typedef struct network_router_s {
    struct {
        route_t route;
        route_handler_t handler;
    } *routes;
    size_t routes_count;
} network_router_t;
