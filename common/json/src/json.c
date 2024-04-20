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
#include <stdio.h>

static bool should_toggle_string(const char *content, size_t i)
{
    if (content[i] == '"' && (i == 0 || content[i - 1] != '\\'))
        return true;
    return false;
}

static size_t find_end(const char *content, size_t i)
{
    int count = 0;
    bool in_string = false;

    for (; content[i]; i++) {
        if (should_toggle_string(content, i))
            in_string = !in_string;
        if (in_string)
            continue;
        if (content[i] == '{' || content[i] == '[')
            count++;
        if (content[i] == '}' || content[i] == ']')
            count--;
        if (count == 0 &&
            (content[i] == ',' || content[i] == '}' || content[i] == ']'))
            return content[i] == ',' ? i - 1 : i;
    }
    return i;
}

static char *get_json_value(const char *content)
{
    size_t end = find_end(content, 0);
    char *value = calloc(end + 2, sizeof(char));

    strncpy(value, content, end + 1);
    value[end + 1] = '\0';
    return value;
}

static char *get_json_key(const char *content, size_t start)
{
    size_t i = start;
    size_t end_of_name;
    size_t start_of_name;
    char *key = NULL;

    for (; i > 0 && content[i] != '"'; i--);
    if (content[i] != '"')
        return NULL;
    end_of_name = i;
    for (i--; i > 0 && content[i] != '"'; i--);
    if (content[i] != '"')
        return NULL;
    start_of_name = i;
    key = calloc((end_of_name - start_of_name), sizeof(char));
    strncpy(key, content + start_of_name + 1, end_of_name - start_of_name - 1);
    key[end_of_name - start_of_name - 1] = '\0';
    return key;
}

static void json_split_consumer(const char *content, size_t *count,
    split_t ***split, size_t *i)
{
    split_t *tmp = NULL;
    size_t end = find_end(content, (*i));

    if (content[(*i)] == ':') {
        tmp = malloc(sizeof(split_t));
        tmp->value = get_json_value(content + (*i) + 1);
        tmp->key = get_json_key(content, (*i));
        (*i) += strlen(tmp->value);
        (*split) = realloc((*split), sizeof(split_t *) * (*count + 2));
        (*split)[*count] = tmp;
        (*split)[*count + 1] = NULL;
        (*count)++;
    }
}

void json_split_array_consumer(const char *content, size_t *count,
    split_t ***split, size_t *i)
{
    split_t *tmp = malloc(sizeof(split_t));

    tmp->value = get_json_value(content + (*i));
    tmp->key = NULL;
    (*i) += strlen(tmp->value);
    (*split) = realloc((*split), sizeof(split_t *) * (*count + 2));
    (*split)[*count] = tmp;
    (*split)[*count + 1] = NULL;
    (*count)++;
}

split_t **json_split(const char *content, bool is_array)
{
    split_t **split = malloc(sizeof(split_t *) * 1);
    size_t count = 0;
    bool in_string = false;

    split[0] = NULL;
    for (size_t i = 0; i < strlen(content); i++) {
        if (is_array) {
            json_split_array_consumer(content, &count, &split, &i);
            continue;
        }
        if (should_toggle_string(content, i))
            in_string = !in_string;
        if (in_string)
            continue;
        json_split_consumer(content, &count, &split, &i);
    }
    return split;
}

json_object_type_t json_get_type(const char *value)
{
    if (value[0] == '{')
        return JSON_OBJECT_TYPE_OBJECT;
    if (value[0] == '[')
        return JSON_OBJECT_TYPE_ARRAY;
    if (value[0] == '"')
        return JSON_OBJECT_TYPE_STRING;
    if (value[0] == 't' || value[0] == 'f')
        return JSON_OBJECT_TYPE_BOOLEAN;
    if (value[0] == 'n')
        return JSON_OBJECT_TYPE_NULL;
    if (strchr(value, '.'))
        return JSON_OBJECT_TYPE_FLOAT;
    return JSON_OBJECT_TYPE_NUMBER;
}

json_parser_t json_get_parser(json_object_type_t type)
{
    switch (type) {
        case JSON_OBJECT_TYPE_OBJECT:
            return (json_parser_t) &json_object_parse;
        case JSON_OBJECT_TYPE_ARRAY:
            return (json_parser_t) &json_array_parse;
        case JSON_OBJECT_TYPE_STRING:
            return (json_parser_t) &json_string_parse;
        case JSON_OBJECT_TYPE_BOOLEAN:
            return (json_parser_t) &json_boolean_parse;
        case JSON_OBJECT_TYPE_NULL:
            return (json_parser_t) &json_null_parse;
        case JSON_OBJECT_TYPE_FLOAT:
            return (json_parser_t) &json_float_parse;
        default:
            return (json_parser_t) &json_number_parse;
    }
}

json_t *json_parse(const char *content)
{
    char *striped = NULL;
    json_object_type_t type = JSON_OBJECT_TYPE_NULL;
    json_parser_t parser = NULL;
    json_t *new = NULL;

    if (content == NULL || strlen(content) == 0)
        return NULL;
    striped = json_strip(content);
    type = json_get_type(striped);
    parser = json_get_parser(type);
    new = parser(striped);
    free(striped);
    return new;
}
