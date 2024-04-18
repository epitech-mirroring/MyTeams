/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "network/sockets.h"

waiting_sockets_t *waiting_sockets_init(void)
{
    waiting_sockets_t *waiting_sockets = calloc(1, sizeof(waiting_sockets_t));

    if (waiting_sockets == NULL)
        return NULL;
    waiting_sockets->sockets = NULL;
    waiting_sockets->sockets_count = 0;
    return waiting_sockets;
}

void waiting_sockets_destroy(waiting_sockets_t *waiting_sockets)
{
    if (waiting_sockets == NULL)
        return;
    for (size_t i = 0; i < waiting_sockets->sockets_count; i++) {
        close(waiting_sockets->sockets[i].socket);
    }
    free(waiting_sockets->sockets);
    free(waiting_sockets);
}
