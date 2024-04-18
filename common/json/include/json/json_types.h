/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <stdbool.h>
#include <stddef.h>
#ifndef __APPLE__
    #define __USE_GNU
    #define _GNU_SOURCE
#endif

/**
 * @brief Enum for the different types of JSON objects
 */
typedef enum json_object_type_e {
    JSON_OBJECT_TYPE_STRING,
    JSON_OBJECT_TYPE_NUMBER,
    JSON_OBJECT_TYPE_FLOAT,
    JSON_OBJECT_TYPE_OBJECT,
    JSON_OBJECT_TYPE_ARRAY,
    JSON_OBJECT_TYPE_BOOLEAN,
    JSON_OBJECT_TYPE_NULL
} json_object_type_t;

/**
 * @brief Struct for JSON objects
 */
typedef struct json_s {
    char *key;
    json_object_type_t type;
} json_t;

/**
 * @brief Struct for JSON object (map of key-value pairs)
 * @note This "inherits" from json_t
 */
typedef struct json_object_s {
    json_t base;
    json_t **values;
    size_t size;
} json_object_t;

/**
 * @brief Struct for JSON array (list of values)
 * @note This "inherits" from json_t
 */
typedef struct json_array_s {
    json_t base;
    json_t **values;
    size_t size;
} json_array_t;

/**
 * @brief Struct for JSON string
 * @note This "inherits" from json_t
 */
typedef struct json_string_s {
    json_t base;
    char *value;
} json_string_t;

/**
 * @brief Struct for JSON number (stored as long)
 * @note This "inherits" from json_t
 */
typedef struct json_number_s {
    json_t base;
    long value;
} json_number_t;

/**
 * @brief Struct for JSON float (stored as double)
 * @note This "inherits" from json_t
 */
typedef struct json_float_s {
    json_t base;
    double value;
} json_float_t;

/**
 * @brief Struct for JSON boolean
 * @note This "inherits" from json_t
 */
typedef struct json_boolean_s {
    json_t base;
    bool value;
} json_boolean_t;

/**
 * @brief Struct for JSON null (this has no value)
 * @note This "inherits" from json_t
 */
typedef struct json_null_s {
    json_t base;
} json_null_t;

typedef struct split_s {
    char *key;
    char *value;
} split_t;

typedef json_t *(*json_parser_t)(const char *content);
typedef void *(*json_destructor_t)(json_t *json);
typedef char *(*json_serializer_t)(json_t *json);
