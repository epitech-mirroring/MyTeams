/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <string.h>
#include "network/router.h"

response_t *create_server_error_response(void)
{
    response_t *response = calloc(1, sizeof(response_t));
    const char *body = "{\"error\":\"Internal server error\"}";

    response->header.status_code = 500;
    response->header.content_length = strlen(body);
    response->body = strdup(body);
    return response;
}

response_t *create_not_found_response(void)
{
    response_t *response = calloc(1, sizeof(response_t));
    const char *body = "{\"error\":\"Not found\"}";

    response->header.status_code = 404;
    response->header.content_length = strlen(body);
    response->body = strdup(body);
    return response;
}
