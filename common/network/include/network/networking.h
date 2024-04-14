/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "json/json_types.h"
#include "network_types.h"

api_handler_t *network_create_api_handler(host_t *host);
request_t *network_create_request(route_t route, param_t params[PARAMS_MAX],
    json_t *body);
request_t *network_create_request_no_params(route_t route,
    json_t *body);
request_t *network_create_request_no_body(route_t route,
    param_t params[PARAMS_MAX]);
request_t *network_create_request_no_params_no_body(route_t route);
void network_send_request(api_handler_t *handler, request_t *request,
    network_promise_consumer_t consumer);
void destroy_api_handler(api_handler_t *handler);
