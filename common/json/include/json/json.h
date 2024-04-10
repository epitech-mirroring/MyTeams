/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "json_types.h"
#include "json/json_object.h"
#include "json/json_array.h"
#include "json/json_string.h"
#include "json/json_boolean.h"
#include "json/json_null.h"
#include "json/json_number.h"
#include "json/json_float.h"

/**
 * @brief Split values from a JSON string
 * @param content The JSON string
 * @param is_array If the JSON is an array
 * @return An array of split_t
 */
split_t **json_split(const char *content, bool is_array);
/**
 * @brief Parse a JSON string
 * @param content The JSON string
 * @return The parsed JSON object
 * @note This will return NULL if the JSON is invalid
 */
json_t *json_parse(const char *content);
/**
 * @brief Get the type of a JSON value
 * @param value The JSON value
 * @return The type of the JSON value
 */
json_object_type_t json_get_type(const char *value);
/**
 * @brief Get the parser for a JSON type
 * @param type The JSON type
 * @return A pointer to the parser function for the type
 */
json_parser_t json_get_parser(json_object_type_t type);
/**
 * @brief Get the destructor for a JSON type
 * @param type The JSON type
 * @return A pointer to the destructor function for the type
 */
json_destructor_t json_get_destructor(json_object_type_t type);
/**
 * @brief Destroy a JSON object
 * @param json The JSON object
 */
void json_destroy(json_t *json);
/**
 * @brief Destroy a split_t array
 * @param split The split_t array
 */
void split_destroy(split_t **split);
/**
 * @brief Get the serializer for a JSON type
 * @param type The JSON type
 * @return A pointer to the serializer function for the type
 */
json_serializer_t json_get_serializer(json_object_type_t type);
/**
 * @brief Serialize a JSON object
 * @param json The JSON object
 * @return The serialized JSON string
 */
char *json_serialize(json_t *json);
/**
 * @brief Load a JSON object from a file
 * @param json The JSON object
 * @return The JSON object deserialized from the file
 */
json_t *json_load_from_file(const char *path);
/**
 * @brief Save a JSON object to a file
 * @param json The JSON object
 * @param path The path to the file
 */
void json_save_to_file(json_t *json, const char *path);
/**
 * @brief Remove all spaces, tabs and line breaks from a string
 * @param str The string to strip
 * @return The stripped string
 */
char *json_strip(const char *str);
