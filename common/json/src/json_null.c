/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/json_null.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

json_null_t *json_null_create(const char *key)
{
    json_null_t *new = malloc(sizeof(json_null_t));

    new->base.type = JSON_OBJECT_TYPE_NULL;
    new->base.key = strdup(key == NULL ? "root" : key);
    return new;
}

json_null_t *json_null_parse(const char *content)
{
    (void) content;
    return json_null_create(NULL);
}

void json_null_destroy(json_null_t *json)
{
    free(json->base.key);
    free(json);
}

char *json_null_serialize(json_null_t *json)
{
    char *res = NULL;

    (void) json;
    asprintf(&res, "null");
    return res;
}
