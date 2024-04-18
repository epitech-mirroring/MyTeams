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

ws_manager_t *ws_manager_init(void)
{
    ws_manager_t *ws_manager = calloc(1, sizeof(ws_manager_t));

    if (ws_manager == NULL)
        return NULL;
    ws_manager->ws = waiting_sockets_init();
    if (ws_manager->ws == NULL) {
        free(ws_manager);
        return NULL;
    }
    ws_manager->running = false;
    return ws_manager;
}

void ws_manager_destroy(ws_manager_t *ws_manager)
{
    waiting_sockets_destroy(ws_manager->ws);
    free(ws_manager);
}
