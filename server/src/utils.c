/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server_utils.h"
#include "network/dto.h"
#include <stdlib.h>
#include <string.h>

response_t create_error(int status_code, const char *status_message,
    const char *name, const char *message)
{
    response_t response = {0};
    json_object_t *res_body = json_object_create(NULL);
    json_string_t *name_json = json_string_create("error_name", name);
    json_string_t *message_json = json_string_create("error_message", message);
    char *body = NULL;

    json_object_add(res_body, (json_t *) name_json);
    json_object_add(res_body, (json_t *) message_json);
    body = json_serialize((json_t *) res_body);
    json_destroy((json_t *) res_body);
    response.status = status_code;
    response.status_message = strdup(status_message);
    response.body = body;
    response_add_header(&response, "Content-Type", "application/json");
}

response_t create_success(int status_code, const char *status_message)
{
    response_t response = {0};

    response.status = status_code;
    response.status_message = strdup(status_message);
    response.body = strdup("");
}

void destroy(char *str, json_t *req_body, json_t *res_body)
{
    free(str);
    json_destroy(req_body);
    json_destroy(res_body);
}
