/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "network/network_manager.h"
#include "network/networking.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

api_handler_t *network_create_api_handler(host_t *host)
{
    api_handler_t *handler = malloc(sizeof(api_handler_t));

    if (!handler)
        return NULL;
    handler->host = host;
    handler->manager = network_manager_create();
    handler->running = true;
    return handler;
}

static response_header_t *receive_response_header(int socket)
{
    response_header_t *header = calloc(1, sizeof(response_header_t));
    char *header_str = calloc(sizeof(response_header_t), sizeof(char));

    if (header == NULL || header_str == NULL)
        return NULL;
    recv(socket, header_str, sizeof(response_header_t), 0);
    memcpy(header, header_str, sizeof(response_header_t));
    free(header_str);
    return header;
}

static response_t *receive_response(response_header_t *header, int socket)
{
    response_t *response = calloc(1, sizeof(response_t));
    char *content_str = calloc(header->content_length, sizeof(char));

    if (response == NULL || content_str == NULL)
        return NULL;
    recv(socket, content_str, header->content_length + sizeof(param_t) *
        PARAMS_MAX, 0);
    response->header = *header;
    response->body = calloc(header->content_length, sizeof(char));
    if (response->body == NULL)
        return NULL;
    memcpy(response->body, content_str, header->content_length);
    return response;
}

static void network_receive_response_consumer(int socket, void *data)
{
    request_promises_t *promise = (request_promises_t *)data;
    response_header_t *header = receive_response_header(socket);
    response_t *response = NULL;

    if (header == NULL) {
        close(socket);
        free(promise);
        return;
    }
    response = receive_response(header, socket);
    if (response == NULL) {
        close(socket);
        free(header);
        free(promise);
        return;
    }
    promise->consumer(response);
    free(header);
    free(promise);
    close(socket);
}

static void network_send_request_consumer(int socket, void *data)
{
    request_promises_t *promise = (request_promises_t *)data;
    char *request_str = serialize_request(promise->request);
    waiting_socket_t *w = malloc(sizeof(waiting_socket_t));

    if (request_str == NULL || w == NULL) {
        close(socket);
        free(promise);
        free(w);
        return;
    }
    send(socket, request_str, promise->request->header.content_length +
        sizeof(request_header_t) + sizeof(param_t) * PARAMS_MAX, 0);
    free(request_str);
    w->socket = socket;
    w->mode = READ;
    w->data = promise;
    w->consumer = network_receive_response_consumer;
    network_manager_add_waiting_socket(promise->handler->manager, w);
}

void network_send_request(api_handler_t *handler, request_t *request,
    network_promise_consumer_t consumer)
{
    int socket = socket_create_client(handler->host);
    waiting_socket_t *waiting_socket;
    request_promises_t *promise;

    if (socket == -1)
        return;
    waiting_socket = malloc(sizeof(waiting_socket_t));
    promise = malloc(sizeof(request_promises_t));
    if (waiting_socket == NULL || promise == NULL) {
        close(socket);
        free(promise);
        free(waiting_socket);
        return;
    }
    *(promise) = (request_promises_t){.handler = handler, .request = request,
        .consumer = consumer};
    *(waiting_socket) = (waiting_socket_t){.socket = socket, .mode = WRITE,
        .data = promise};
    waiting_socket->consumer = network_send_request_consumer;
    network_manager_add_waiting_socket(handler->manager, waiting_socket);
}

void destroy_api_handler(api_handler_t *handler)
{
    network_manager_destroy(handler->manager);
    free(handler);
}
