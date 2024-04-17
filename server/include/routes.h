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
/**
 * @brief Global middleware (run on every request)
 * @param request The request that will be processed
 * @param data The instance of roundtable_server_t
 * @return The request with the server attached
 */
request_t *global_middleware(request_t *request, void *data);

// -------------------------- ROUTES --------------------------------
/**
 * @brief Route for the login
 * POST /login
 * @param request The request to process
 * @return The response
 * @note see documentation/routes.md
 */
response_t *login_route(request_t *request);
