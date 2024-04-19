/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "network/types.h"

typedef struct route_handler_s {
    char *path;
    response_t (*handler)(request_t *req, void *data);
    void *data;
} route_handler_t;

typedef struct middleware_s {
    char *path;
    response_t *(*handler)(request_t *req, void *data);
    void *data;
} middleware_t;

typedef struct router_s {
    route_handler_t *routes;
    size_t routes_count;
    middleware_t *middlewares;
    size_t middlewares_count;
    ws_manager_t *ws_manager;
    host_t host;
} router_t;

/**
 * @brief Create a router object
 * @param host The host on which the router will listen
 * @return The initialized router object
 */
router_t *router_init(host_t host);
/**
 * @brief Destroy a router object
 * @param router The router object to destroy
 */
void router_destroy(router_t *router);
/**
 * @brief Add a route to the router
 * @param router The router object to add the route to
 * @param path The path of the route (will be copied)
 * @param handler The handler of the route
 * @param data Custom data to pass to the handler (can be NULL)
 */
void router_add_route(router_t *router, const char *path,
    response_t (*handler)(request_t *req, void *data), void *data);
/**
 * @brief Add a middleware to the router
 * @param router the router object to add the middleware to
 * @param path the path of the middleware (will be copied)
 * @param handler the handler of the middleware
 * @param data custom data to pass to the handler (can be NULL)
 * @note Middlewares are executed before routes
 */
void router_add_middleware(router_t *router, const char *path,
    response_t *(*handler)(request_t *req, void *data), void *data);
/**
 * @brief Start the router
 * @param router The router object to start
 */
void router_start(router_t *router);
/**
 * @brief Accept a connection on the router
 * @param ws The waiting server socket to accept the connection on
 * @return true if the connection was accepted, false otherwise
 */
bool router_accept_connection(waiting_socket_t *ws);
/**
 * @brief Handle a request on the router
 * @param socket The waiting socket to handle the request on
 * @return true if the socket should be kept open, false otherwise
 */
bool router_handle_request(waiting_socket_t *socket);
/**
 * @brief Handle the sending of a response on the router
 * @param socket The waiting socket to send the response on
 * @return true if the socket should be kept open, false otherwise
 */
bool waiting_socket_send_response(waiting_socket_t *socket);
/**
 * @brief Get a route that matches the given path
 * @param router The router object to get the route from
 * @param path The path to match
 * @return The route handler that matches the path, or NULL if no route matches
 */
route_handler_t *router_get_route(router_t *router, const char *path);
/**
 * @brief Get all middlewares that match the given path
 * @param router the router object to get the middlewares from
 * @param path the path to match
 * @return An array of middlewares that match the path
 * @note The array is NULL-terminated
 */
middleware_t **router_get_middlewares(router_t *router, const char *path);
