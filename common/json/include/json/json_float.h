/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "json_types.h"

/**
 * @brief Create a json float with a key and a value
 * @param key The key (name) of the float
 * @param value The value of the float
 * @return A json float with the key and value
 */
json_float_t *json_float_create(const char *key, double value);
/**
 * @brief Parse a json float from a string
 * @param content The string to parse
 * @return The parsed json float
 */
json_float_t *json_float_parse(const char *content);
/**
 * @brief Destroy a json float
 * @param json The json float to destroy
 */
void json_float_destroy(json_float_t *json);
/**
 * @brief Serialize a json float
 * @param json The json float to serialize
 * @return The serialized json float
 */
char *json_float_serialize(json_float_t *json);
