/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdio.h>
#include "network/sockets.h"

static void waiting_sockets_reset_fd(waiting_sockets_t *waiting_sockets,
    fd_set *fds, waiting_socket_mode_t mode)
{
    FD_ZERO(fds);
    for (size_t i = 0; i < waiting_sockets->sockets_count; i++) {
        if (waiting_sockets->sockets[i].mode == mode) {
            FD_SET(waiting_sockets->sockets[i].socket, fds);
        }
    }
}

static void waiting_sockets_recompute_max_fd(
    waiting_sockets_t *waiting_sockets)
{
    int max_fd = 0;

    for (size_t i = 0; i < waiting_sockets->sockets_count; i++) {
        if (waiting_sockets->sockets[i].socket > max_fd) {
            max_fd = waiting_sockets->sockets[i].socket;
        }
    }
    waiting_sockets->max_fd = max_fd;
}

void waiting_sockets_reset_fds(waiting_sockets_t *waiting_sockets)
{
    waiting_sockets_reset_fd(waiting_sockets,
                            &waiting_sockets->read_fds, READ);
    waiting_sockets_reset_fd(waiting_sockets,
                            &waiting_sockets->write_fds, WRITE);
    waiting_sockets_recompute_max_fd(waiting_sockets);
}
