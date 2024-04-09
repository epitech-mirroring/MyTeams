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
 * @brief Create a json string with a key and a value
 * @param key The key (name) of the string
 * @param value The value of the string (will be copied)
 * @return A json string with the key and value
 */
json_string_t *json_string_create(const char *key, const char *value);
/**
 * @brief Parse a json string from a string
 * @param content The string to parse
 * @return The parsed json string
 */
json_string_t *json_string_parse(const char *content);
/**
 * @brief Destroy a json string
 * @param json The json string to destroy
 */
void json_string_destroy(json_string_t *json);
/**
 * @brief Serialize a json string
 * @param json The json string to serialize
 * @return The serialized json string
 */
char *json_string_serialize(json_string_t *json);
