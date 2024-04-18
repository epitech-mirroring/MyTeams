/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "network/sockets.h"

int waiting_sockets_select(waiting_sockets_t *waiting_sockets)
{
    struct timeval timeout = {0, 250};

    waiting_sockets_reset_fds(waiting_sockets);
    return select(waiting_sockets->max_fd + 1, &waiting_sockets->read_fds,
        &waiting_sockets->write_fds, NULL, &timeout);
}
