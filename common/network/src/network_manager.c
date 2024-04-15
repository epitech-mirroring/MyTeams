/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "network/network_manager.h"

void network_manager_handle_waiting_sockets(network_manager_t *manager)
{
    waiting_socket_t **called = calloc(1, sizeof(waiting_socket_t *));
    size_t to_remove_count = 0;

    if (called == NULL)
        return;
    network_manager_reset_fds(manager);
    select(manager->max_fd + 1, &manager->read_fds, &manager->write_fds,
        NULL, NULL);
    call_set_sockets(manager, &called, &to_remove_count);
    for (size_t i = 0; i < to_remove_count; i++) {
        called[i]->consumer(called[i]->socket, called[i]->data);
        network_manager_remove_waiting_socket(manager, called[i]->socket,
            called[i]->mode);
    }
    free(called);
}

network_manager_t *network_manager_create(void)
{
    network_manager_t *new = malloc(sizeof(network_manager_t));

    if (new == NULL)
        return NULL;
    new->waiting_sockets = NULL;
    new->waiting_sockets_count = 0;
    new->max_fd = 0;
    return new;
}

void network_manager_destroy(network_manager_t *manager)
{
    for (size_t i = 0; i < manager->waiting_sockets_count; i++) {
        free(manager->waiting_sockets[i]);
    }
    free(manager->waiting_sockets);
    free(manager);
}

void destroy_request(request_t *request)
{
    free(request);
}
