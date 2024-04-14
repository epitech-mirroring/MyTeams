/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "network/network_manager.h"
#include "network/networking.h"
#include "json/json.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

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

request_t *network_create_request(route_t route,
    param_t params[PARAMS_MAX], json_t *body)
{
    request_t *request = calloc(1, sizeof(request_t));
    char *body_str = json_serialize(body);

    if (!request)
        return NULL;
    request->header.route = route;
    request->header.content_length = body_str == NULL ? 0 : strlen(body_str);
    for (int i = 0; i < PARAMS_MAX; i++)
        request->params[i] = params[i];
    request->body = body_str;
    return request;
}

request_t *network_create_request_no_params(route_t route, json_t *body)
{
    param_t params[PARAMS_MAX] = {0};

    return network_create_request(route, params, body);
}

request_t *network_create_request_no_body(route_t route,
    param_t params[PARAMS_MAX])
{
    return network_create_request(route, params, NULL);
}

request_t *network_create_request_no_params_no_body(route_t route)
{
    param_t params[PARAMS_MAX] = {0};

    return network_create_request(route, params, NULL);
}

static void network_receive_response_consumer(int socket, void *data) {
    network_promise_consumer_t consumer = (network_promise_consumer_t)data;
    response_header_t *response_header;
    char *response_header_str = calloc(sizeof(response_header_t), sizeof(char));
    char *response_content_str = NULL;
    response_t *response = NULL;

    if (response_header_str == NULL) {
        close(socket);
        return;
    }
    recv(socket, response_header_str, sizeof(response_header_t), 0);
    response_header = deserialize_response_header(response_header_str);
    response_content_str = calloc(sizeof(param_t) * PARAMS_MAX + response_header->content_length, sizeof(char));
    if (response_content_str == NULL) {
        close(socket);
        free(response_header_str);
        return;
    }
    recv(socket, response_content_str, sizeof(param_t) * PARAMS_MAX + response_header->content_length, 0);
    response = deserialize_response(response_header, response_content_str);
    consumer(response);
    free(response_header_str);
}

static void network_send_request_consumer(int socket, void *data) {
    request_promises_t *promise = (request_promises_t *)data;
    char *request_str = serialize_request(promise->request);
    waiting_socket_t *waiting_socket = malloc(sizeof(waiting_socket_t));

    if (request_str == NULL || waiting_socket == NULL) {
        close(socket);
        free(promise);
        free(waiting_socket);
        return;
    }
    send(socket, request_str, promise->request->header.content_length + sizeof(request_header_t) + sizeof(param_t) * PARAMS_MAX, 0);
    free(request_str);
    waiting_socket->socket = socket;
    waiting_socket->mode = READ;
    waiting_socket->data = promise->consumer;
    waiting_socket->consumer = network_receive_response_consumer;
    network_manager_add_waiting_socket(promise->handler->manager, waiting_socket);
    destroy_request(promise->request);
    free(promise);
}

void network_send_request(api_handler_t *handler, request_t *request, network_promise_consumer_t consumer)
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
    promise->request = request;
    promise->consumer = consumer;
    promise->handler = handler;
    waiting_socket->socket = socket;
    waiting_socket->mode = WRITE;
    waiting_socket->data = promise;
    waiting_socket->consumer = network_send_request_consumer;
    network_manager_add_waiting_socket(handler->manager, waiting_socket);
}

void destroy_api_handler(api_handler_t *handler)
{
    network_manager_destroy(handler->manager);
    free(handler);
}
