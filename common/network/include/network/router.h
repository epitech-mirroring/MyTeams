/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "network_types.h"


// --------------------------- Router -----------------------------
/**
 * @brief Create a new network router
 * @param host The host to bind the router to
 * @return The new network router
 */
network_router_t *network_router_create(host_t host);
/**
 * @brief Destroy a network router
 * @param router The router to destroy
 */
void network_router_destroy(network_router_t *router);
/**
 * @brief Add a route to a network router
 * @param router The router to add the route to
 * @param route The route to add
 * @param handler The handler for the route
 */
void network_router_add_route(network_router_t *router, route_t route, route_handler_t handler);
/**
 * @brief Remove a route from a network router
 * @param router The router to remove the route from
 * @param route The route to remove
 */
void network_router_remove_route(network_router_t *router, route_t route);
/**
 * @brief Listen for incoming connections
 * @param router The router to listen with
 */
void network_router_listen(network_router_t *router);

// --------------------------- Middlewares -----------------------------
/**
 * @brief Add a middleware to a network router
 * @param router The router to add the middleware to
 * @param middleware The middleware to add
 */
void network_router_add_middleware(network_router_t *router, middlewares_t middleware);
/**
 * @brief Remove a middleware from a network router
 * @param router The router to remove the middleware from
 * @param route The route to remove the middleware from
 */
void network_router_remove_middleware(network_router_t *router, route_t route);

// ----------------------------- Socket ---------------------------------
/**
 * @brief Accept a new socket connection
 * @param server_socket The server socket to accept the connection from
 * @param data The data to pass to the consumer
 */
void router_socket_accept(int server_socket, void *data);
/**
 * @brief Handle a request from a client
 * @param client_socket The client socket to handle the request from
 * @param data The data to pass to the consumer
 */
void router_handle_request(int client_socket, void *data);

// ------------------------------- Requests ------------------------------
/**
 * @brief Read a request from a client
 * @param client_socket The client socket to read the request from
 * @return The request read from the client
 */
request_t *router_read_request(int client_socket);

// ----------------------------- Responses --------------------------------
/**
 * @brief Send a response to a client
 * @param client_socket The client socket to send the response to
 * @param data The data to send
 */
void router_send_response(int client_socket, void *data);


