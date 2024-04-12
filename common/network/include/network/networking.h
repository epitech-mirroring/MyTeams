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
/**
 * @brief Make an API call
 * @param method The request method
 * @param path The path to call
 * @param body The body of the request
 * @param consumer The consumer for the promise
 */
void api_call(request_method_t method, const char *path, json_t *body, network_promise_consumer_t consumer);
/**
 * @brief Make an API call with parameters
 * @param method The request method
 * @param path The path to call
 * @param params The parameters for the request
 * @param body The body of the request
 * @param consumer The consumer for the promise
 */
void api_call_with_params(request_method_t method, const char *path, param_t *params, json_t *body, network_promise_consumer_t consumer);
