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
 * @brief Create a json array with a key
 * @param key The key (name) of the array
 * @return An empty json array with the key
 */
json_array_t *json_array_create(const char *key);
/**
 * @brief Add any json type to a json array
 * @param json The json array to add to
 * @param obj The json type to add
 * @note this will reallocate the values array
 */
void json_array_add(json_array_t *json, json_t *obj);
/**
 * @brief Get a json object from a json array
 * @param json The json array to get from
 * @param index The index of the object to get
 * @return The json object at the index
 */
json_t *json_array_get(json_array_t *json, size_t index);
/**
 * @brief Parse a json array from a string
 * @param content The string to parse
 * @return The parsed json array
 */
json_array_t *json_array_parse(const char *content);
/**
 * @brief Destroy a json array
 * @param json The json array to destroy
 */
void json_array_destroy(json_array_t *json);
/**
 * @brief Serialize a json array
 * @param json The json array to serialize
 * @return The serialized json array
 */
char *json_array_serialize(json_array_t *json);
