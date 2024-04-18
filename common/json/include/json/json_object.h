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
 * @brief Create a json object with a key
 * @param key The key (name) of the object
 * @return An empty json object with the key
 */
json_object_t *json_object_create(const char *key);
/**
 * @brief Add any json type to a json object
 * @param json The json object to add to
 * @param obj The json type to add
 * @note this will reallocate the values array
 */
void json_object_add(json_object_t *json, json_t *obj);
/**
 * @brief Get a json object from a json object
 * @param json The json object to get from
 * @param key The key of the object to get
 * @return The json object with the key
 */
json_t *json_object_get(json_object_t *json, char *key);
/**
 * @brief Parse a json object from a string
 * @param content The string to parse
 * @return The parsed json object
 */
json_object_t *json_object_parse(const char *content);
/**
 * @brief Destroy a json object
 * @param json The json object to destroy
 */
void json_object_destroy(json_object_t *json);
/**
 * @brief Serialize a json object
 * @param json The json object to serialize
 * @return The serialized json object
 */
char *json_object_serialize(json_object_t *json);
/**
 * @brief Check if a json object has a key
 * @param json The json object to check
 * @param key The key to check for
 * @return true if the key is present, false otherwise
 */
bool json_object_has_key(json_object_t *object, const char *key);
