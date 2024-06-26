/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "network/router.h"

// -------------------------- MIDDLEWARES --------------------------------

// -------------------------- ROUTES --------------------------------
/**
 * @brief Route for the login
 * POST /login
 * @param request The request to process
 * @return The response
 * @note see documentation/routes.md
 */
response_t login_route(request_t *request, void *data);
/**
 * @brief Route for the logout
 * POST /logout
 * @param request The request to process
 * @param data The instance of roundtable_server_t
 * @return The response
 */
response_t logout_route(request_t *request, void *data);
/**
 * @brief Route to send a direct message between two clients
 * POST /messages/send
 * @param request The request to process
 * @param data The instance of roundtable_server_t
 * @return The response
 * @note see documentation/routes.md
 */
response_t send_dm_route(request_t *request, void *data);
/**
 * @brief Route to get the direct messages between two clients
 * GET /messages
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 */
response_t get_dms_route(request_t *request, void *data);
/**
 * @brief Route to create a team
 * POST /teams/create
 * @param request The request to process
 * @param data The instance of roundtable_server_t
 * @return the response
 * @note see documentation/routes.md
 */
response_t create_team_route(request_t *request, void *data);

/**
 * @brief Route to get the user
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 */
response_t user_route(request_t *request, void *data);
/**
 * @brief Route to get the teams
 * GET /teams
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 * @note see documentation/routes.md
 */
response_t get_teams_route(request_t *request, void *data);
/**
 * @brief Route to join a team
 * POST /teams/join
 * @param request The request to process
 * @param data The instance of roundtable_server_t
 * @return the response
 * @note see documentation/routes.md
 */
response_t join_team_route(request_t *request, void *data);
/**
 * @brief Route to leave a team
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 * @note see documentation/routes.md
 */
response_t leave_team_route(request_t *request, void *data);
/**
 * @brief Route to get the users of a team
 * GET /teams/users
 * @param request The request to process
 * @param data The instance of roundtable_server_t
 * @return The response
 * @note see documentation/routes.md
 */
response_t team_users_route(request_t *request, void *data);
/**
 * @brief Route to create a channel
 * POST /teams/channels/create
 * @param request The request to process
 * @param data The instance of roundtable_server_t
 * @return The response
 * @note see documentation/routes.md
 */
response_t create_channel_route(request_t *request, void *data);
/**
 * @brief Route to get the list of all the user
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 *
*/
response_t users_route(request_t *request, void *data);
/**
 * @brief Route to check if a user is subscribed to a team
 * GET /teams/is-subscribed?team-uuid=...
 * @param request The request to process
 * @param data The instance of roundtable_server_t
 * @return The response ({subscribed: true/false})
 * @note see documentation/routes.md
 */
response_t is_subscribed_route(request_t *request, void *data);

/**
 * @brief Route to get the list of all the channels
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 * @note see documentation/routes.md
 */
response_t get_channels_route(request_t *request, void *data);

/**
 * @brief Route to create a thread
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 * @note see documentation/routes.md
 */
response_t create_thread_route(request_t *request, void *data);
/**
 * @brief Route to get the list of all the threads
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 * @note see documentation/routes.md
 */
response_t get_threads_route(request_t *request, void *data);
/**
 * @brief Route to create a reply
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 * @note see documentation/routes.md
 */
response_t create_reply_route(request_t *request, void *data);
/**
 * @brief Route to get the list of all the replies
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 * @note see documentation/routes.md
 */
response_t get_replies_route(request_t *req, void *data);
/**
 * @brief Route to get the list of all the events
 * GET /events
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 * @note see documentation/routes.md
 */
response_t events_route(request_t *request, void *data);
/**
 * @brief Route to update the status of a user
 * POST /status
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 */
response_t update_status_route(request_t *request, void *data);
/**
 * @brief Route to get the list of all the direct messages
 * GET /messages
 * @param request the request to process
 * @param data the instance of roundtable_server_t
 * @return the response
 */
response_t list_direct_messages_route(request_t *request, void *data);
