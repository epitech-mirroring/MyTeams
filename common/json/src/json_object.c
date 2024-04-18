/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/json_object.h"
#include "json/json.h"
#include <stdlib.h>
#include <string.h>

json_object_t *json_object_create(const char *key)
{
    json_object_t *new = malloc(sizeof(json_object_t));

    new->base.type = JSON_OBJECT_TYPE_OBJECT;
    new->base.key = strdup(key == NULL ? "root" : key);
    new->values = malloc(sizeof(json_t) * 1);
    new->values[0] = NULL;
    new->size = 0;
    return new;
}

void json_object_add(json_object_t *json, json_t *obj)
{
    json_t **new_values = NULL;

    new_values = realloc(json->values, sizeof(json_t) * (json->size + 2));
    if (new_values == NULL)
        return;
    json->values = new_values;
    json->values[json->size] = obj;
    json->values[json->size + 1] = NULL;
    json->size++;
}

json_t *json_object_get(json_object_t *json, char *key)
{
    for (size_t i = 0; i < json->size; i++) {
        if (strcmp(json->values[i]->key, key) == 0)
            return json->values[i];
    }
    return NULL;
}

json_object_t *json_object_parse(const char *content)
{
    json_object_t *new = json_object_create(NULL);
    json_t *tmp = NULL;
    char *inside = strndup(content + 1, strlen(content) - 2);
    split_t **lines = json_split(inside, false);
    size_t i = 0;

    while (lines[i] != NULL) {
        tmp = json_parse(lines[i]->value);
        if (tmp->key != NULL)
            free(tmp->key);
        tmp->key = strdup(lines[i]->key);
        json_object_add(new, tmp);
        i++;
    }
    free(inside);
    split_destroy(lines);
    return new;
}

void json_object_destroy(json_object_t *json)
{
    for(size_t i = 0; i < json->size; i++) {
        json_destroy(json->values[i]);
    }
    if (json->values != NULL)
        free(json->values);
    if (json->base.key != NULL)
        free(json->base.key);
}
