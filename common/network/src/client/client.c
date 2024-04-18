/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include "network/api_client.h"
#include "network/manager.h"
#include "network/sockets.h"
#include "network/dto.h"

api_client_t *api_client_init(char *host, int port)
{
    api_client_t *client = calloc(1, sizeof(api_client_t));

    if (client == NULL)
        return NULL;
    client->host = calloc(1, sizeof(host_t));
    if (client->host == NULL) {
        free(client);
        return NULL;
    }
    *(client->host) = (host_t){.ip = host, .port = port};
    client->ws_manager = ws_manager_init();
    if (client->ws_manager == NULL) {
        free(client->host);
        free(client);
        return NULL;
    }
    return client;
}

void api_client_destroy(api_client_t *client)
{
    ws_manager_destroy(client->ws_manager);
    free(client->host->ip);
    free(client->host);
    free(client);
}

static void destroy_request_data(request_data_t *req_data)
{
    destroy_request(req_data->req);
    free(req_data);
}

static bool api_client_send_request_callback(waiting_socket_t *ws)
{
    request_data_t *req_data = ws->data;
    response_t *res = NULL;
    char *tmp = NULL;

    if (ws->mode == WRITE) {
        tmp = serialize_request(*req_data->req);
        send(ws->socket, tmp, strlen(tmp), 0);
        free(tmp);
        ws->mode = READ;
    } else {
        tmp = calloc(BUFFER_SIZE, sizeof(char));
        recv(ws->socket, tmp, BUFFER_SIZE, 0);
        res = deserialize_response(tmp);
        req_data->handler(res, req_data);
        free(tmp);
        destroy_response(res);
        destroy_request_data(req_data);
        return false;
    }
    return true;
}

void api_client_send_request(api_client_t *client, request_t *req,
    response_handler_t handler, void *data)
{
    int socket = socket_create_client(*client->host);
    waiting_socket_t *ws = NULL;
    request_data_t *req_data = calloc(1, sizeof(request_data_t));

    if (socket == -1)
        return;
    ws = waiting_sockets_add_socket(client->ws_manager->ws,
        socket, WRITE, &api_client_send_request_callback);
    if (ws == NULL)
        return;
    *req_data = (request_data_t){.client = client, .data = data,
        .handler = handler, .req = req};
    ws->data = req_data;
}
