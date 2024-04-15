/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <string.h>
#include "network/network_types.h"
#include "json/json.h"

request_t *network_create_request(route_t route,
    param_t params[PARAMS_MAX], json_t *body)
{
    request_t *request = calloc(1, sizeof(request_t));
    char *body_str = json_serialize(body);

    if (!request)
        return NULL;
    request->header.route = route;
    request->header.content_length = body_str == NULL ? 0 : strlen(body_str);
    for (int i = 0; i < PARAMS_MAX; i++)
        request->params[i] = params[i];
    request->body = body_str;
    return request;
}

request_t *network_create_request_no_params(route_t route, json_t *body)
{
    param_t params[PARAMS_MAX] = {0};

    return network_create_request(route, params, body);
}

request_t *network_create_request_no_body(route_t route,
    param_t params[PARAMS_MAX])
{
    return network_create_request(route, params, NULL);
}

request_t *network_create_request_no_params_no_body(route_t route)
{
    param_t params[PARAMS_MAX] = {0};

    return network_create_request(route, params, NULL);
}
