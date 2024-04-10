/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/json_boolean.h"
#include <stdlib.h>
#ifndef __APPLE__
#define __USE_GNU
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>

json_boolean_t *json_boolean_create(const char *key, bool value)
{
    json_boolean_t *new = malloc(sizeof(json_boolean_t));

    new->base.type = JSON_OBJECT_TYPE_BOOLEAN;
    new->base.key = strdup(key == NULL ? "root" : key);
    new->value = value;
    return new;
}

json_boolean_t *json_boolean_parse(const char *content)
{
    bool value = strcmp(content, "true") == 0;

    return json_boolean_create(NULL, value);
}

void json_boolean_destroy(json_boolean_t *json)
{
    free(json->base.key);
    free(json);
}

char *json_boolean_serialize(json_boolean_t *json)
{
    char *res = NULL;

    asprintf(&res, "%s", json->value ? "true" : "false");
    return res;
}
