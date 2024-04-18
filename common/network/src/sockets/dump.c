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

void empty_waiting_sockets(waiting_sockets_t *waiting_sockets,
    bool close_socket)
{
    if (close_socket) {
        for (size_t i = 0; i < waiting_sockets->sockets_count; i++) {
            close(waiting_sockets->sockets[i].socket);
        }
    }
    free(waiting_sockets->sockets);
    waiting_sockets->sockets = NULL;
    waiting_sockets->sockets_count = 0;
}
