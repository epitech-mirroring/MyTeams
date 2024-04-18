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
