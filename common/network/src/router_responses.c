/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include "network/router.h"
#include "network/network_manager.h"

void router_send_response(int client_socket, void *data)
{
    response_t *response = (response_t *)data;
    char *response_str = serialize_response(response);

    send(client_socket, response_str, response->header.content_length
        + sizeof(response->header), 0);
    close(client_socket);
    free(response_str);
    free(response);
}
