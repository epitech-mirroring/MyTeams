/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "network/dto.h"
#include "regex.h"

void destroy_request(request_t *req)
{
    for (size_t i = 0; i < req->headers_count; i++) {
        free(req->headers[i].key);
        free(req->headers[i].value);
    }
    for (size_t i = 0; i < req->params_count; i++) {
        free(req->params[i].key);
        free(req->params[i].value);
    }
    free(req->headers);
    free(req->params);
    free(req->body);
}

static char *parse_param(request_t *req, char *param)
{
    char *key = NULL;
    char *value = NULL;
    regex_t regex;
    regmatch_t matches[3];

    regcomp(&regex, "([^=]+)=([^&]+)", REG_EXTENDED);
    if (regexec(&regex, param, 3, matches, 0) == 0) {
        key = strndup(param + matches[1].rm_so,
            matches[1].rm_eo - matches[1].rm_so);
        value = strndup(param + matches[2].rm_so,
            matches[2].rm_eo - matches[2].rm_so);
    }
    regfree(&regex);
    request_add_param(req, key, value);
    param = strtok(NULL, "&");
    return param;
}

static void parse_uri(request_t *req, char *uri)
{
    char *path = strtok(uri, "?");
    char *params = strtok(NULL, "?");
    char *param = NULL;

    strncpy(req->route.path, path, strlen(path));
    if (params == NULL)
        return;
    param = strtok(params, "&");
    while (param != NULL) {
        param = parse_param(req, param);
    }
}

static void parse_request_first_line(const char *buffer, request_t *req)
{
    regex_t regex;
    regmatch_t matches[3];
    char *uri = NULL;

    regcomp(&regex, "^(GET|POST|PUT|DELETE) ([^ ]+) HTTP/1.1", REG_EXTENDED);
    if (regexec(&regex, buffer, 3, matches, 0) == 0) {
        strncpy((*req).route.method, buffer + matches[1].rm_so,
            matches[1].rm_eo - matches[1].rm_so);
        uri = strndup(buffer + matches[2].rm_so,
            matches[2].rm_eo - matches[2].rm_so);
        parse_uri(req, uri);
        free(uri);
    }
    regfree(&regex);
}

static void request_parse_header(request_t *req, const char *headers,
    size_t line_end)
{
    char *line = strndup(headers, line_end);
    regex_t regex;
    regmatch_t m[3];
    char *key = NULL;
    char *value = NULL;

    regcomp(&regex, "^([^:]+): (.+)$", REG_EXTENDED);
    if (regexec(&regex, line, 3, m, 0) == 0) {
        key = strndup(line + m[1].rm_so, m[1].rm_eo - m[1].rm_so);
        value = strndup(line + m[2].rm_so, m[2].rm_eo - m[2].rm_so);
        request_add_header(req, key, value);
        free(key);
        free(value);
    }
    regfree(&regex);
    free(line);
}

static void request_parse_headers(char *buffer, request_t *req,
    size_t *line_start)
{
    char *headers = NULL;
    size_t line_end;

    line_end = strcspn(buffer, "\r\n");
    headers = buffer + (*line_start);
    while (line_end != 0) {
        request_parse_header(req, headers, line_end);
        (*line_start) += line_end + 2;
        headers = buffer + (*line_start);
        line_end = strcspn(headers, "\r\n");
    }
}

request_t *deserialize_request(char *buffer)
{
    request_t *req = calloc(1, sizeof(request_t));
    size_t line_start = 0;

    parse_request_first_line(buffer, req);
    request_parse_headers(buffer, req, &line_start);
    req->body = strdup(buffer + line_start + 2);
    return req;
}

char *serialize_request(request_t req)
{
    char *serialized = calloc(BUFFER_SIZE, sizeof(char));

    if (serialized == NULL)
        return NULL;
    sprintf(serialized, "%s %s HTTP/1.1\r\n",
            req.route.method, serialize_request_path(&req));
    for (size_t i = 0; i < req.headers_count; i++) {
        sprintf(serialized + strlen(serialized), "%s: %s\r\n",
            req.headers[i].key, req.headers[i].value);
    }
    sprintf(serialized + strlen(serialized), "Content-Length: %ld\r\n",
        strlen(req.body));
    sprintf(serialized + strlen(serialized), "\r\n%s", req.body);
    return serialized;
}
