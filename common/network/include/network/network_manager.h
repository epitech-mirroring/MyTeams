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
char *serialize_params(param_t params[PARAMS_MAX]);
char *serialize_param(param_t param);
char *serialize_route(route_t route);
char *serialize_request_method(request_method_t method);
char *serialize_request_header(request_header_t header);
char *serialize_request(request_t *request);
char *serialize_response_header(response_header_t header);
char *serialize_status_code(status_code_t code);
char *serialize_size_t(size_t size);
char *serialize_response(response_t *response);
request_header_t deserialize_request_header(char *header_str);
request_t *deserialize_request(char *header_str, char *content);
response_header_t deserialize_response_header(char *header_str);
response_t *deserialize_response(char *header_str, char *content);
