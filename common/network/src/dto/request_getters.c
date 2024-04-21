/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "network/dto.h"

char *to_lower(const char *str)
{
    char *new_str = strdup(str);

    for (size_t i = 0; i < strlen(new_str); i++)
        new_str[i] = (char) tolower(new_str[i]);
    return new_str;
}

bool request_has_param(request_t *req, char *key)
{
    char *new_key = to_lower(key);
    char *tmp_key = NULL;

    for (size_t i = 0; i < req->params_count; i++) {
        tmp_key = to_lower(req->params[i].key);
        if (strcmp(req->params[i].key, key) == 0) {
            free(new_key);
            free(tmp_key);
            return true;
        }
        free(tmp_key);
    }
    free(new_key);
    return false;
}

char *request_get_header(request_t *req, char *key)
{
    char *new_key = to_lower(key);
    char *tmp_key = NULL;

    for (size_t i = 0; i < req->headers_count; i++) {
        tmp_key = to_lower(req->headers[i].key);
        if (strcmp(tmp_key, new_key) == 0) {
            free(new_key);
            free(tmp_key);
            return req->headers[i].value;
        }
        free(tmp_key);
    }
    free(new_key);
    return NULL;
}

char *request_get_param(request_t *req, char *key)
{
    char *new_key = to_lower(key);
    char *tmp_key = NULL;

    for (size_t i = 0; i < req->params_count; i++) {
        tmp_key = to_lower(req->params[i].key);
        if (strcmp(tmp_key, new_key) == 0) {
            free(new_key);
            free(tmp_key);
            return req->params[i].value;
        }
        free(tmp_key);
    }
    free(new_key);
    return NULL;
}
