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
#include <regex.h>

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
    sprintf(serialized + strlen(serialized), "Content-Length: %ld\r\n",
        strlen(res.body));
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

static void parse_response_first_line(const char *buffer, response_t *resp)
{
    regex_t regex;
    regmatch_t matches[3];
    char *uri = NULL;

    regcomp(&regex, "^HTTP/1.1 ([0-9]{3}) (.*)", REG_EXTENDED);
    if (regexec(&regex, buffer, 3, matches, 0) == 0) {
        resp->status = atoi(buffer + matches[1].rm_so);
        resp->status_message = strndup(buffer + matches[2].rm_so,
            matches[2].rm_eo - matches[2].rm_so);
    }
    regfree(&regex);
}

static void response_parse_header(response_t *resp, const char *headers,
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
        response_add_header(resp, key, value);
        free(key);
        free(value);
    }
    regfree(&regex);
    free(line);
}

static void response_parse_headers(char *buffer, response_t *resp,
    size_t *line_start)
{
    char *headers = NULL;
    size_t line_end;

    line_end = strcspn(buffer, "\r\n");
    headers = buffer + (*line_start);
    while (line_end != 0) {
        response_parse_header(resp, headers, line_end);
        (*line_start) += line_end + 2;
        headers = buffer + (*line_start);
        line_end = strcspn(headers, "\r\n");
    }
}

response_t *deserialize_response(char *buffer)
{
    response_t *resp = calloc(1, sizeof(response_t));
    size_t line_start = 0;

    parse_response_first_line(buffer, resp);
    response_parse_headers(buffer, resp, &line_start);
    resp->body = strdup(buffer + line_start + 2);
    return resp;
}
