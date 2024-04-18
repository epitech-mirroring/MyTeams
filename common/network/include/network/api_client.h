/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once

#include "types.h"

typedef struct api_client_s {
    host_t *host;
    ws_manager_t *ws_manager;
} api_client_t;

api_client_t *api_client_init(char *host, int port);
void api_client_destroy(api_client_t *client);

typedef struct request_data_s request_data_t;

typedef void (*response_handler_t)(response_t *res, request_data_t *data);

typedef struct request_data_s {
    api_client_t *client;
    void *data;
    response_handler_t handler;
    request_t *req;
} request_data_t;

void api_client_send_request(api_client_t *client, request_t *req,
    response_handler_t handler, void *data);
