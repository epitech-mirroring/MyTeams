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
void network_manager_add_waiting_socket(network_manager_t *manager, waiting_socket_t *socket);
/**
 * @brief Remove a waiting socket from a network manager
 * @param manager The manager to remove the socket from
 * @param socket The socket to remove
 */
void network_manager_remove_waiting_socket(network_manager_t *manager, int socket);
/**
 * @brief Handle all waiting sockets in a network manager
 * @param manager The manager to handle the sockets with
 */
void network_manager_handle_waiting_sockets(network_manager_t *manager);

/**
 * @brief Serialize parameters
 * @param params The parameters to serialize
 * @return The serialized parameters
 */
char *serialize_params(param_t params[PARAMS_MAX]);
/**
 * @brief Serialize a parameter
 * @param param The parameter to serialize
 * @return The serialized parameter
 */
char *serialize_param(param_t param);
/**
 * @brief Serialize a route
 * @param route The route to serialize
 * @return The serialized route
 */
char *serialize_route(route_t route);
/**
 * @brief Serialize a request method
 * @param method The method to serialize
 * @return The serialized method
 */
char *serialize_request_method(request_method_t method);
/**
 * @brief Serialize a request header
 * @param header The header to serialize
 * @return The serialized header
 */
char *serialize_request_header(request_header_t header);
/**
 * @brief Serialize a request
 * @param request The request to serialize
 * @return The serialized request
 */
char *serialize_request(request_t *request);


/**
 * @brief Serialize a response header
 * @param header The header to serialize
 * @return The serialized header
 */
char *serialize_response_header(response_header_t header);
/**
 * @brief Serialize a status code
 * @param code The code to serialize
 * @return The serialized code
 */
char *serialize_status_code(status_code_t code);
/**
 * @brief Serialize a size_t
 * @param size The size to serialize
 * @return The serialized size
 */
char *serialize_size_t(size_t size);
/**
 * @brief Serialize a response
 * @param response The response to serialize
 * @return The serialized response
 */
char *serialize_response(response_t *response);

/**
 * @brief Deserialize a request header
 * @param header_str The header string to deserialize
 * @return The deserialized header
 */
request_header_t deserialize_request_header(char *header_str);

/**
 * @brief Deserialize a request
 * @param header_str The header string to deserialize
 * @param content The content string to deserialize
 * @return The deserialized request
 */
request_t *deserialize_request(char *header_str, char *content);
/**
 * @brief Deserialize a response header
 * @param header_str The header string to deserialize
 * @return The deserialized header
 */
response_header_t deserialize_response_header(char *header_str);
/**
 * @brief Deserialize a response
 * @param header_str The header string to deserialize
 * @param content The content string to deserialize
 * @return The deserialized response
 */
response_t *deserialize_response(char *header_str, char *content);
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
