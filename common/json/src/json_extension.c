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

json_destructor_t json_get_destructor(json_object_type_t type)
{
    switch (type) {
        case JSON_OBJECT_TYPE_OBJECT:
            return (json_destructor_t) &json_object_destroy;
        case JSON_OBJECT_TYPE_ARRAY:
            return (json_destructor_t) &json_array_destroy;
        case JSON_OBJECT_TYPE_STRING:
            return (json_destructor_t) &json_string_destroy;
        case JSON_OBJECT_TYPE_BOOLEAN:
            return (json_destructor_t) &json_boolean_destroy;
        case JSON_OBJECT_TYPE_NULL:
            return (json_destructor_t) &json_null_destroy;
        case JSON_OBJECT_TYPE_FLOAT:
            return (json_destructor_t) &json_float_destroy;
        default:
            return (json_destructor_t) &json_number_destroy;
    }
}

void json_destroy(json_t *json)
{
    json_destructor_t destructor = NULL;

    if (json == NULL)
        return;
    destructor = json_get_destructor(json->type);
    destructor(json);
}

void split_destroy(split_t **splits)
{
    for (int i = 0; splits[i] != NULL; i++) {
        free(splits[i]->key);
        free(splits[i]->value);
        free(splits[i]);
    }
    free(splits);
}

char *json_strip(const char *str)
{
    char *res = malloc(sizeof(char) * 1);
    size_t end = strlen(str);
    bool in_string = false;

    if (res == NULL)
        return NULL;
    res[0] = '\0';
    for (size_t i = 0; i < end; i++) {
        if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
            in_string = !in_string;
        if (in_string || (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')) {
            res = realloc(res, sizeof(char) * (strlen(res) + 2));
            strncat(res, str + i, 1);
        }
    }
    return res;
}
