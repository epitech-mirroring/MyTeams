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

response_header_t *deserialize_response_header(char *str)
{
    response_header_t *header = calloc(1, sizeof(response_header_t));

    if (header == NULL)
        return NULL;
    memcpy(header, str, sizeof(response_header_t));
    return header;
}

response_t *deserialize_response(response_header_t *header, char *response_str)
{
    response_t *response = calloc(1, sizeof(response_t));

    if (response == NULL)
        return NULL;
    response->header = *header;
    response->body = calloc(header->content_length, sizeof(char));
    if (response->body == NULL)
        return NULL;
    memcpy(response->body, response_str + sizeof(response_header_t),
            header->content_length);
    free(header);
    return response;
}

request_header_t *deserialize_request_header(char *str)
{
    request_header_t *header = calloc(1, sizeof(request_header_t));

    if (header == NULL)
        return NULL;
    memcpy(header, str, sizeof(request_header_t));
    return header;
}

request_t *deserialize_request(request_header_t *header,
    char *body_with_params)
{
    request_t *request = calloc(1, sizeof(request_t));

    if (request == NULL)
        return NULL;
    request->header = *header;
    memcpy(request->params, body_with_params, sizeof(param_t) * PARAMS_MAX);
    request->body = calloc(header->content_length, sizeof(char));
    if (request->body == NULL)
        return NULL;
    memcpy(request->body, body_with_params + sizeof(param_t) * PARAMS_MAX,
            header->content_length);
    free(header);
    return request;
}
