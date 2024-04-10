/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/json_number.h"
#include <stdlib.h>
#ifndef __APPLE__
#define __USE_GNU
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>

json_number_t *json_number_create(const char *key, long value)
{
    json_number_t *new = malloc(sizeof(json_number_t));

    new->base.type = JSON_OBJECT_TYPE_NUMBER;
    new->base.key = strdup(key == NULL ? "root" : key);
    new->value = value;
    return new;
}

json_number_t *json_number_parse(const char *content)
{
    long value = strtol(content, NULL, 10);

    return json_number_create(NULL, value);
}

void json_number_destroy(json_number_t *json)
{
    free(json->base.key);
    free(json);
}

char *json_number_serialize(json_number_t *json)
{
    char *res = NULL;

    asprintf(&res, "%ld", json->value);
    return res;
}
