/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "network/dto.h"

char *serialize_response(response_t res)
{
    char *serialized = calloc(BUFFER_SIZE, sizeof(char));

    if (serialized == NULL)
        return NULL;
    sprintf(serialized, "HTTP/1.1 %d %s\r\n", res.status, res.status_message);
    for (size_t i = 0; i < res.headers_count; i++) {
        sprintf(serialized + strlen(serialized), "%s: %s\r\n",
            res.headers[i].key, res.headers[i].value);
    }
    sprintf(serialized + strlen(serialized), "\r\n%s", res.body);
    return serialized;
}

void destroy_response(response_t *res)
{
    for (size_t i = 0; i < res->headers_count; i++) {
        free(res->headers[i].key);
        free(res->headers[i].value);
    }
    free(res->status_message);
    free(res->headers);
    free(res->body);
}
