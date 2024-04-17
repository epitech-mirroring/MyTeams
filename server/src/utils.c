/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server_utils.h"
#include "json/json.h"
#include <stdlib.h>

response_t *create_error(int status_code,
    const char *name, const char *message)
{
    response_t *response = calloc(1, sizeof(response_t));
    json_object_t *body = json_object_create(NULL);
    json_string_t *name_json = json_string_create("error_name",
    name);
    json_string_t *message_json = json_string_create("error_message",
    message);
    char *body_str = NULL;

    json_object_add(body, (json_t *) name_json);
    json_object_add(body, (json_t *) message_json);
    body_str = json_serialize((json_t *) body);
    response->header.status_code = status_code;
    response->header.content_length = strlen(body_str);
    response->body = strdup(body_str);
    free(body_str);
    json_destroy((json_t *) body);
    return response;
}

response_t *create_success(int status_code)
{
    response_t *response = calloc(1, sizeof(response_t));

    response->header.status_code = status_code;
    response->header.content_length = 0;
    return response;
}

void destroy(char *str, json_t *req_body, json_t *res_body)
{
    free(str);
    json_destroy(req_body);
    json_destroy(res_body);
}
