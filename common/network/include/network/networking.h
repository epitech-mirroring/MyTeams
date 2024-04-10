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

void api_call(request_method_t method, const char *path, json_t *body, network_promise_consumer_t consumer);
void api_call_with_params(request_method_t method, const char *path, param_t *params, json_t *body, network_promise_consumer_t consumer);
