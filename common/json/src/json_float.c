/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/json_float.h"
#include <stdlib.h>
#ifndef __APPLE__
#define __USE_GNU
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>


json_float_t *json_float_create(const char *key, double value)
{
    json_float_t *new = malloc(sizeof(json_float_t));

    new->base.type = JSON_OBJECT_TYPE_FLOAT;
    new->base.key = strdup(key == NULL ? "root" : key);
    new->value = value;
    return new;
}

json_float_t *json_float_parse(const char *content)
{
    double value = strtod(content, NULL);

    return json_float_create(NULL, value);
}

void json_float_destroy(json_float_t *json)
{
    free(json->base.key);
    free(json);
}

char *json_float_serialize(json_float_t *json)
{
    char *res = NULL;

    asprintf(&res, "%f", json->value);
    return res;
}
