/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/json_string.h"
#include <stdlib.h>
#ifndef __APPLE__
#define __USE_GNU
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>

json_string_t *json_string_create(const char *key, const char *value)
{
    json_string_t *new = malloc(sizeof(json_string_t));

    new->base.type = JSON_OBJECT_TYPE_STRING;
    new->base.key = strdup(key == NULL ? "root" : key);
    new->value = strdup(value);
    return new;
}

json_string_t *json_string_parse(const char *content)
{
    char *stripped = strndup(content + 1, strlen(content) - 2);
    json_string_t *new = json_string_create(NULL, stripped);

    free(stripped);
    return new;
}

void json_string_destroy(json_string_t *json)
{
    free(json->base.key);
    free(json->value);
    free(json);
}

char *json_string_serialize(json_string_t *json)
{
    char *res = NULL;

    asprintf(&res, "\"%s\"", json->value);
    return res;
}
