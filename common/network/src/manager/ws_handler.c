/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "network/manager.h"
#include "network/sockets.h"

static void add_socket_to_remove(int **sockets_to_remove, size_t *count,
    int socket)
{
    int *new_sockets_to_remove = NULL;

    new_sockets_to_remove = realloc(*sockets_to_remove,
                                    sizeof(int) * (*count + 1));
    if (new_sockets_to_remove == NULL)
        return;
    *sockets_to_remove = new_sockets_to_remove;
    (*sockets_to_remove)[*count] = socket;
    (*count)++;
}

void ws_manager_handle_sockets(waiting_sockets_t *ws)
{
    waiting_socket_t *socket = NULL;
    int *sockets_to_remove = NULL;
    size_t sockets_to_remove_count = 0;

    for (size_t i = 0; i < ws->sockets_count; i++) {
        socket = &ws->sockets[i];
        if (!ws_manager_handle_socket(ws, socket)) {
            add_socket_to_remove(&sockets_to_remove, &sockets_to_remove_count,
                socket->socket);
        }
    }
    for (size_t i = 0; i < sockets_to_remove_count; i++) {
        waiting_sockets_remove_socket(ws, sockets_to_remove[i], true);
    }
    free(sockets_to_remove);
}

bool ws_manager_handle_socket(waiting_sockets_t *ws,
    waiting_socket_t *socket)
{
    fd_set *set = socket->mode == READ ? &ws->read_fds :
        &ws->write_fds;

    if (FD_ISSET(socket->socket, set)) {
        return socket->callback(socket);
    }
    return true;
}
