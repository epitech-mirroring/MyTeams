/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <stdlib.h>
#include "network/dto.h"

void request_add_header(request_t *req, const char *key, const char *value)
{
    header_t *new_headers = realloc(req->headers, sizeof(header_t)
        * (req->headers_count + 1));

    if (new_headers == NULL)
        return;
    req->headers = new_headers;
    req->headers[req->headers_count].key = strdup(key);
    req->headers[req->headers_count].value = strdup(value);
    req->headers_count++;
}

void request_add_param(request_t *req, const char *key, const char *value)
{
    param_t *new_params = realloc(req->params, sizeof(param_t)
        * (req->params_count + 1));

    if (new_params == NULL)
        return;
    req->params = new_params;
    req->params[req->params_count].key = strdup(key);
    req->params[req->params_count].value = strdup(value);
    req->params_count++;
}

bool request_has_header(request_t *req, char *key)
{
    char *new_key = to_lower(key);
    char *tmp_key = NULL;

    for (size_t i = 0; i < req->headers_count; i++) {
        tmp_key = to_lower(req->headers[i].key);
        if (strcmp(tmp_key, new_key) == 0) {
            free(new_key);
            free(tmp_key);
            return true;
        }
        free(tmp_key);
    }
    free(new_key);
    return false;
}

char *serialize_request_path(request_t *req)
{
    char *new_path = NULL;
    char *path = strdup(req->route.path);

    for (size_t i = 0; i < req->params_count; i++) {
        new_path = realloc(path, strlen(path) + strlen(req->params[i].key)
            + strlen(req->params[i].value) + 3);
        if (new_path == NULL)
            return NULL;
        path = new_path;
        strcat(path, i == 0 ? "?" : "&");
        strcat(path, req->params[i].key);
        strcat(path, "=");
        strcat(path, req->params[i].value);
    }
    return path;
}
