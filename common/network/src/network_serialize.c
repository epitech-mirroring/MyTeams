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

char *serialize_request(request_t *request)
{
    char *str = calloc(sizeof(request_header_t) + sizeof(param_t) * PARAMS_MAX
        + request->header.content_length, sizeof(char));

    if (str == NULL)
        return NULL;
    memcpy(str, &request->header, sizeof(request_header_t));
    memcpy(str + sizeof(request_header_t), request->params,
        sizeof(param_t) * PARAMS_MAX);
    memcpy(str + sizeof(request_header_t) + sizeof(param_t) * PARAMS_MAX,
        request->body, request->header.content_length);
    return str;
}

char *serialize_response(response_t *response)
{
    char *str = calloc(sizeof(response_header_t) +
        response->header.content_length, sizeof(char));

    if (str == NULL)
        return NULL;
    memcpy(str, &response->header, sizeof(response_header_t));
    memcpy(str + sizeof(response_header_t), response->body,
        response->header.content_length);
    return str;
}
