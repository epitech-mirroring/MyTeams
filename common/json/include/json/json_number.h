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
 * @brief Create a json number with a key and a value
 * @param key The key (name) of the number
 * @param value The value of the number
 * @return A json number with the key and value
 */
json_number_t *json_number_create(const char *key, long value);
/**
 * @brief Parse a json number from a string
 * @param content The string to parse
 * @return The parsed json number
 */
json_number_t *json_number_parse(const char *content);
/**
 * @brief Destroy a json number
 * @param json The json number to destroy
 */
void json_number_destroy(json_number_t *json);
/**
 * @brief Serialize a json number
 * @param json The json number to serialize
 * @return The serialized json number
 */
char *json_number_serialize(json_number_t *json);
