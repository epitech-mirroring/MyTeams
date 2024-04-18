/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <unistd.h>
#include "network/sockets.h"

waiting_socket_t *waiting_sockets_add_socket(
    waiting_sockets_t *waiting_sockets, int socket, waiting_socket_mode_t mode,
    bool (*callback)(waiting_socket_t *))
{
    waiting_socket_t *new_sockets = NULL;

    new_sockets = realloc(waiting_sockets->sockets,
        sizeof(waiting_socket_t) * (waiting_sockets->sockets_count + 1));
    if (new_sockets == NULL)
        return NULL;
    waiting_sockets->sockets = new_sockets;
    waiting_sockets->sockets[waiting_sockets->sockets_count].socket = socket;
    waiting_sockets->sockets[waiting_sockets->sockets_count].mode = mode;
    waiting_sockets->sockets[waiting_sockets->sockets_count].callback
        = callback;
    waiting_sockets->sockets_count++;
    return &waiting_sockets->sockets[waiting_sockets->sockets_count - 1];
}

void waiting_sockets_remove_socket(waiting_sockets_t *waiting_sockets,
    int socket, bool close_socket)
{
    for (size_t i = 0; i < waiting_sockets->sockets_count; i++) {
        if (waiting_sockets->sockets[i].socket == socket) {
            close(close_socket ? socket : 0);
            waiting_sockets->sockets[i] = waiting_sockets->sockets[
                waiting_sockets->sockets_count - 1];
            waiting_sockets->sockets_count--;
            return;
        }
    }
}
