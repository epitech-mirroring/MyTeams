/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "network/network_types.h"

void call_set_sockets(const network_manager_t *manager,
    waiting_socket_t ***called, size_t *called_count)
{
    waiting_socket_t *tmp = NULL;
    waiting_socket_t **tmp_called = NULL;
    fd_set set;

    for (size_t i = 0; i < manager->waiting_sockets_count; i++) {
        tmp = manager->waiting_sockets[i];
        set = tmp->mode == READ ? manager->read_fds : manager->write_fds;
        if (FD_ISSET(tmp->socket, &set)) {
            tmp_called = realloc((*called), sizeof(waiting_socket_t *) * (
                (*called_count) + 2));
            (*called) = tmp_called;
            (*called)[(*called_count)] = tmp;
            (*called)[(*called_count) + 1] = NULL;
            (*called_count)++;
        }
    }
}

void network_manager_reset_fds(network_manager_t *manager)
{
    FD_ZERO(&manager->read_fds);
    FD_ZERO(&manager->write_fds);
    for (size_t i = 0; i < manager->waiting_sockets_count; i++) {
        FD_SET(manager->waiting_sockets[i]->socket,
            manager->waiting_sockets[i]->mode == READ ?
            &manager->read_fds : &manager->write_fds);
    }
}
