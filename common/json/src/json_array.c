/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/json_array.h"
#include "json/json.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

json_array_t *json_array_create(const char *key)
{
    json_array_t *new = malloc(sizeof(json_array_t));

    new->base.type = JSON_OBJECT_TYPE_ARRAY;
    new->base.key = strdup(key == NULL ? "root" : key);
    new->values = malloc(sizeof(json_t) * 1);
    new->values[0] = NULL;
    new->size = 0;
    return new;
}

void json_array_add(json_array_t *json, json_t *obj)
{
    json_t **values = NULL;

    values = realloc(json->values, sizeof(json_t) * (json->size + 2));
    if (values == NULL) {
        fprintf(stderr, "Failed to reallocate json array\n");
        return;
    }
    json->values = values;
    json->values[json->size] = obj;
    json->values[json->size + 1] = NULL;
    json->size++;
}

json_t *json_array_get(json_array_t *json, size_t index)
{
    if (index >= json->size) {
        fprintf(stderr, "Index out of bounds\n");
        return NULL;
    }
    return json->values[index];
}

json_array_t *json_array_parse(const char *content)
{
    json_array_t *new = json_array_create(NULL);
    json_t *tmp = NULL;
    char *inside = strndup(content + 1, strlen(content) - 2);
    split_t **lines = json_split(inside, true);
    size_t i = 0;

    while (lines[i] != NULL) {
        tmp = json_parse(lines[i]->value);
        if (tmp->key != NULL)
            free(tmp->key);
        tmp->key = lines[i]->key;
        json_array_add(new, tmp);
        i++;
    }
    split_destroy(lines);
    return new;
}

void json_array_destroy(json_array_t *json)
{
    for (size_t i = 0; i < json->size; i++) {
        json_destroy(json->values[i]);
        free(json->values[i]);
    }
    if (json->values != NULL)
        free(json->values);
    if (json->base.key != NULL)
        free(json->base.key);
}
