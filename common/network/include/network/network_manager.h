/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "network/network_types.h"

network_manager_t *network_manager_create(void);
void network_manager_destroy(network_manager_t *manager);
int socket_create_client(host_t *host);
int socket_create_server(host_t *host);
void network_manager_add_waiting_socket(network_manager_t *manager, waiting_socket_t *socket);
void network_manager_remove_waiting_socket(network_manager_t *manager, int socket);
void network_manager_handle_waiting_sockets(network_manager_t *manager);
