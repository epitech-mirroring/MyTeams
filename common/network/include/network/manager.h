/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "network/types.h"

/**
 * @brief Init a waiting socket manager
 * @return The initialized waiting socket manager
 */
ws_manager_t *ws_manager_init(void);
/**
 * @brief Destroy a waiting socket manager
 * @param ws_manager The waiting socket manager to destroy
 */
void ws_manager_destroy(ws_manager_t *ws_manager);
/**
 * @brief Start the waiting socket manager
 * @param ws_manager The waiting socket manager to start
 * @note This function is blocking and will run until ws_manager_stop is called
 */
void ws_manager_start(ws_manager_t *ws_manager);
/**
 * @brief Stop the waiting socket manager
 * @param ws_manager The waiting socket manager to stop
 */
void ws_manager_stop(ws_manager_t *ws_manager);
/**
 * @brief Run the waiting socket manager once
 * @param ws_manager The waiting socket manager to run
 */
void ws_manager_run_once(ws_manager_t *ws_manager);
/**
 * @brief Handle the sockets of the waiting socket manager
 * @param ws The waiting socket list to handle
 * @param socket The socket to handle
 * @return true if the socket was handled, false otherwise
 */
bool ws_manager_handle_socket(waiting_sockets_t *ws,
    waiting_socket_t *socket);
/**
 * @brief Handle the sockets of the waiting socket manager
 * @param ws The waiting socket list to handle
 */
void ws_manager_handle_sockets(waiting_sockets_t *ws);
