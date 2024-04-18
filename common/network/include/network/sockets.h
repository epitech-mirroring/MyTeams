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
 * @brief Init the waiting sockets struct
 * @return The structure with no sockets
 */
waiting_sockets_t *waiting_sockets_init(void);
/**
 * @brief Destroy the waiting sockets struct
 * @param waiting_sockets The structure to destroy
 */
void waiting_sockets_destroy(waiting_sockets_t *waiting_sockets);
/**
 * @brief Reset the file descriptors of the waiting sockets
 * @param waiting_sockets The structure to reset
 * @note Also recompute the max fd
 */
void waiting_sockets_reset_fds(waiting_sockets_t *waiting_sockets);
/**
 * @brief Add a socket to the waiting sockets
 * @param waiting_sockets The structure to add the socket to
 * @param socket The socket to add
 * @param mode The mode to add the socket as
 * @param callback The callback to call when the socket is ready
 * @return The waiting socket structure or NULL if an error occurred
 */
waiting_socket_t *waiting_sockets_add_socket(
    waiting_sockets_t *waiting_sockets, int socket, waiting_socket_mode_t mode,
    bool (*callback)(waiting_socket_t *));
/**
 * @brief Create a client socket
 * @param host The host to connect to
 * @return The client socket or -1 if an error occurred
 */
int socket_create_client(host_t host);
/**
 * @brief Create a server socket
 * @param host The host to create the server on
 * @return The server socket or -1 if an error occurred
 */
int socket_create_server(host_t host);
/**
 * @brief Select on the waiting sockets
 * @param waiting_sockets The structure to select on
 * @return The return value of the select call
 */
int waiting_sockets_select(waiting_sockets_t *waiting_sockets);
/**
 * @brief Remove a socket from the waiting sockets
 * @param waiting_sockets The structure to remove the socket from
 * @param socket The socket to remove
 * @param close_socket Whether to close the socket or not
 */
void waiting_sockets_remove_socket(waiting_sockets_t *waiting_sockets,
    int socket, bool close_socket);
/**
 * @brief Empty the waiting sockets
 * @param waiting_sockets The structure to empty
 * @param close_socket Whether to close the sockets or not
 */
void empty_waiting_sockets(waiting_sockets_t *waiting_sockets,
    bool close_socket);
