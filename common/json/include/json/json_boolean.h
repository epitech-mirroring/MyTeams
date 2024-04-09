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
 * @brief Create a json boolean with a key and a value
 * @param key The key (name) of the boolean
 * @param value The value of the boolean
 * @return A json boolean with the key and value
 */
json_boolean_t *json_boolean_create(const char *key, bool value);
/**
 * @brief Parse a json boolean from a string
 * @param content The string to parse
 * @return The parsed json boolean
 */
json_boolean_t *json_boolean_parse(const char *content);
/**
 * @brief Destroy a json boolean
 * @param json The json boolean to destroy
 */
void json_boolean_destroy(json_boolean_t *json);
/**
 * @brief Serialize a json boolean
 * @param json The json boolean to serialize
 * @return The serialized json boolean
 */
char *json_boolean_serialize(json_boolean_t *json);
