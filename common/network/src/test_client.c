/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "network/networking.h"
#include "network/network_manager.h"

api_handler_t *handler_global = NULL;

static void handle_response(response_t *response)
{
    printf("Response received: %s\n", response->body);
    if (handler_global)
        handler_global->running = false;
}

int main(int argc, char **argv)
{
    host_t *host = malloc(sizeof(host_t));
    api_handler_t *handler;
    request_t *request;

    if (argc != 3) {
        free(host);
        return 84;
    }
    host->port = (int) strtol(argv[1], NULL, 10);
    host->ip = argv[2];
    handler = network_create_api_handler(host);
    if (!handler) {
        free(host);
        return 84;
    }
    request = network_create_request_no_params_no_body((route_t) {GET, "/api/v1/test"});
    if (!request) {
        free(host);
        destroy_api_handler(handler);
        return 84;
    }
    handler_global = handler;
    network_send_request(handler, request, handle_response);
    while (handler->running) {
        network_manager_handle_waiting_sockets(handler->manager);
        usleep(100);
    }
    destroy_api_handler(handler);
    free(host);
    return 0;
}