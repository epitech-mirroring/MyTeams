/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include "network/dto.h"

bool request_has_param(request_t *req, char *key)
{
    for (size_t i = 0; i < req->params_count; i++) {
        if (strcmp(req->params[i].key, key) == 0)
            return true;
    }
    return false;
}

char *request_get_header(request_t *req, char *key)
{
    for (size_t i = 0; i < req->headers_count; i++) {
        if (strcmp(req->headers[i].key, key) == 0)
            return req->headers[i].value;
    }
    return NULL;
}
