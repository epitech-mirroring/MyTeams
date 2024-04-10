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
 * @brief Create a json null with a key
 * @param key The key (name) of the null
 * @return A json null with a key
 */
json_null_t *json_null_create(const char *key);
/**
 * @brief Parse a json null from a string
 * @param content The string to parse
 * @return The parsed json null
 */
json_null_t *json_null_parse(const char *content);
/**
 * @brief Destroy a json null
 * @param json The json null to destroy
 */
void json_null_destroy(json_null_t *json);
/**
 * @brief Serialize a json null
 * @param json The json null to serialize
 * @return The serialized json null
 */
char *json_null_serialize(json_null_t *json);
