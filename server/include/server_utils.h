/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "network/router.h"
#include "json/json.h"
#include "server.h"

// -------------------------- NETWORK --------------------------------
typedef struct status_message_s {
    int status_code;
    const char *message;
} status_message_t;

extern const status_message_t status_messages[];
response_t create_error(int status_code,
    const char *name, const char *message);
response_t create_success(int status_code, const char *body);
void destroy(char *str, json_t *req_body, json_t *res_body);
const char *get_status_message(int status_code);
response_t create_options_response(void);
#define IS_METHOD(r, m) (strcmp(r->route.method, m) == 0)
