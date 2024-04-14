/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <string.h>
#include "network/network_manager.h"

ssize_t network_manager_find_waiting_socket(network_manager_t *manager,
    int socket, waiting_socket_mode_t mode)
{
    ssize_t i = 0;

    while (i < (ssize_t) manager->waiting_sockets_count) {
        if (manager->waiting_sockets[i]->socket == socket &&
            manager->waiting_sockets[i]->mode == mode)
            return i;
        i++;
    }
    return -1;
}

void network_manager_remove_waiting_socket(network_manager_t *manager,
    int socket, waiting_socket_mode_t mode)
{
    ssize_t index = network_manager_find_waiting_socket(manager, socket, mode);
    waiting_socket_t **tmp = NULL;

    if (index == -1)
        return;
    free(manager->waiting_sockets[index]);
    for (size_t i = index; i < manager->waiting_sockets_count - 1; i++)
        manager->waiting_sockets[i] = manager->waiting_sockets[i + 1];
    tmp = realloc(manager->waiting_sockets, sizeof(waiting_socket_t *) *
        manager->waiting_sockets_count);
    if (tmp == NULL)
        return;
    manager->waiting_sockets = tmp;
    manager->waiting_sockets_count--;
}

void network_manager_add_waiting_socket(network_manager_t *manager,
    waiting_socket_t *socket)
{
    waiting_socket_t **tmp = NULL;

    tmp = realloc(manager->waiting_sockets, sizeof(waiting_socket_t *) *
        (manager->waiting_sockets_count + 2));
    if (tmp == NULL)
        return;
    manager->waiting_sockets = tmp;
    manager->waiting_sockets[manager->waiting_sockets_count] = socket;
    manager->waiting_sockets[manager->waiting_sockets_count + 1] = NULL;
    manager->waiting_sockets_count++;
    manager->max_fd = socket->socket > manager->max_fd ?
        socket->socket : manager->max_fd;
}
