/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/json.h"
#include <stdlib.h>
#include <string.h>
#ifndef __APPLE__
#define __USE_GNU
#define _GNU_SOURCE
#endif
#include <stdio.h>

json_serializer_t json_get_serializer(json_object_type_t type)
{
    switch (type) {
        case JSON_OBJECT_TYPE_OBJECT:
            return (json_serializer_t) &json_object_serialize;
        case JSON_OBJECT_TYPE_ARRAY:
            return (json_serializer_t) &json_array_serialize;
        case JSON_OBJECT_TYPE_STRING:
            return (json_serializer_t) &json_string_serialize;
        case JSON_OBJECT_TYPE_BOOLEAN:
            return (json_serializer_t) &json_boolean_serialize;
        case JSON_OBJECT_TYPE_NULL:
            return (json_serializer_t) &json_null_serialize;
        case JSON_OBJECT_TYPE_FLOAT:
            return (json_serializer_t) &json_float_serialize;
        default:
            return (json_serializer_t) &json_number_serialize;
    }
}

char *json_object_serialize(json_object_t *json)
{
    char *res = malloc(sizeof(char) * 3);
    char *tmp = NULL;

    res[0] = '{';
    res[1] = '\0';
    for (int i = 0; json->values[i] != NULL; i++) {
        asprintf(&tmp, "\"%s\":%s", json->values[i]->key,
            json_serialize(json->values[i]));
        res = realloc(res, sizeof(char) * (strlen(res) + strlen(tmp) + 3));
        strcat(res, tmp);
        if (json->values[i + 1] != NULL)
            strcat(res, ",");
        free(tmp);
    }
    strcat(res, "}");
    return res;
}

char *json_array_serialize(json_array_t *json)
{
    char *res = malloc(sizeof(char) * 3);
    char *tmp = NULL;

    res[0] = '[';
    res[1] = '\0';
    for (int i = 0; json->values[i] != NULL; i++) {
        asprintf(&tmp, "%s", json_serialize(json->values[i]));
        res = realloc(res, sizeof(char) * (strlen(res) + strlen(tmp) + 3));
        strcat(res, tmp);
        if (json->values[i + 1] != NULL)
            strcat(res, ",");
        free(tmp);
    }
    strcat(res, "]");
    return res;
}

char *json_serialize(json_t *json)
{
    json_serializer_t serializer = NULL;

    if (json == NULL)
        return NULL;
    serializer = json_get_serializer(json->type);
    return serializer(json);
}
