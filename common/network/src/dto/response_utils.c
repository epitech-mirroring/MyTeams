/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <string.h>
#include "network/dto.h"

void response_add_header(response_t *res, char *key, char *value)
{
    header_t *new_headers = realloc(res->headers, sizeof(header_t)
        * (res->headers_count + 1));

    if (new_headers == NULL)
        return;
    res->headers = new_headers;
    res->headers[res->headers_count].key = strdup(key);
    res->headers[res->headers_count].value = strdup(value);
    res->headers_count++;
}
