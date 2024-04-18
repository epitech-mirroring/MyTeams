/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "network/manager.h"
#include "network/sockets.h"

void ws_manager_start(ws_manager_t *ws_manager)
{
    ws_manager->running = true;
    while (ws_manager->running) {
        ws_manager_run_once(ws_manager);
    }
}

void ws_manager_stop(ws_manager_t *ws_manager)
{
    ws_manager->running = false;
}

void ws_manager_run_once(ws_manager_t *ws_manager)
{
    waiting_sockets_t *ws = ws_manager->ws;

    if (waiting_sockets_select(ws) == -1) {
        waiting_sockets_destroy(ws);
        return;
    }
    ws_manager_handle_sockets(ws);
}
