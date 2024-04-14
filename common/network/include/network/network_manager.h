/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "network/network_types.h"


/**
 * @brief Create a new network manager
 * @return The new network manager
 */
network_manager_t *network_manager_create(void);
/**
 * @brief Destroy a network manager
 * @param manager The manager to destroy
 */
void network_manager_destroy(network_manager_t *manager);
/**
 * @brief Create a new socket
 * @param host The host to bind the socket to
 * @return The new socket
 */
int socket_create_client(host_t *host);
/**
 * @brief Create a new server socket
 * @param host The host to bind the socket to
 * @return The new server socket
 */
int socket_create_server(host_t *host);
/**
 * @brief Add a waiting socket to a network manager
 * @param manager The manager to add the socket to
 * @param socket The socket to add
 */
void network_manager_add_waiting_socket(network_manager_t *manager,
    waiting_socket_t *socket);
/**
 * @brief Remove a waiting socket from a network manager
 * @param manager The manager to remove the socket from
 * @param socket The socket to remove
 * @param mode The mode of the socket
 */
void network_manager_remove_waiting_socket(network_manager_t *manager,
    int socket, waiting_socket_mode_t mode);
/**
 * @brief Handle all waiting sockets in a network manager
 * @param manager The manager to handle the sockets with
 */
void network_manager_handle_waiting_sockets(network_manager_t *manager);
/**
 * @brief Destroy a request
 * @param request The request to destroy
 */
void destroy_request(request_t *request);
/**
 * @brief Destroy a response
 * @param response The response to destroy
 */
void destroy_response(response_t *response);
/**
 * @brief Transform a response into bytes
 * @param response The response to transform
 * @return The byte array of the response
 */
char *serialize_response(response_t *response);
/**
 * @brief Transform a request into bytes
 * @param request The request to transform
 * @return The byte array of the request
 */
char *serialize_request(request_t *request);
/**
 * @brief Transform bytes into a request
 * @param header The header of the request
 * @param request_str The byte array to transform
 * @return The request
 */
request_t *deserialize_request(request_header_t *header,
    char *body_with_params);
/**
 * @brief Transform bytes into a response
 * @param header The header of the response
 * @param response_str The byte array to transform
 * @return The response
 */
response_t *deserialize_response(response_header_t *header,
    char *response_str);
/**
 * @brief Transform a request header into bytes
 * @param header The header to transform
 * @return The byte array of the header
 */
request_header_t *deserialize_request_header(char *header_str);
/**
 * @brief Transform a response header into bytes
 * @param header The header to transform
 * @return The byte array of the header
 */
response_header_t *deserialize_response_header(char *header_str);
