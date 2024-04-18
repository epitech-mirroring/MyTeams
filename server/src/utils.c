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

const status_message_t status_messages[] = {
    {200, "OK"},
    {201, "Created"},
    {204, "No Content"},
    {400, "Bad Request"},
    {401, "Unauthorized"},
    {403, "Forbidden"},
    {404, "Not Found"},
    {500, "Internal Server Error"},
    {501, "Not Implemented"},
    {502, "Bad Gateway"},
    {503, "Service Unavailable"},
    {504, "Gateway Timeout"},
    {505, "HTTP Version Not Supported"},
    {0, NULL}
};

const char *get_status_message(int status_code)
{
    for (size_t i = 0; status_messages[i].status_code != 0; i++) {
        if (status_messages[i].status_code == status_code)
            return status_messages[i].message;
    }
    return "Unknown";
}

response_t create_error(int status_code, const char *name, const char *message)
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
    response.status_message = strdup(get_status_message(status_code));
    response.headers_count = 0;
    response.headers = NULL;
    response.body = body;
    response_add_header(&response, "Content-Type", "application/json");
    return response;
}

response_t create_success(int status_code, const char *body)
{
    response_t response = {0};

    response.status = status_code;
    response.status_message = strdup(get_status_message(status_code));
    response.body = strdup(body);
    response.headers_count = 0;
    response.headers = NULL;
    return response;
}

void destroy(char *str, json_t *req_body, json_t *res_body)
{
    free(str);
    json_destroy(req_body);
    json_destroy(res_body);
}
