/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <stdbool.h>

typedef unsigned char uuid_t[16];

/**
 * @brief Compare two uuids
 * @param uu1 the first uuid
 * @param uu2 the second uuid
 * @return true if the uuids are the same, false otherwise
 */
bool uuid_compare(const uuid_t uu1, const uuid_t uu2);
/**
 * @brief Transform a string to a uuid
 * @param uu the uuid to transform
 * @return the string representation of the uuid
 */
char *uuid_to_string(const uuid_t uu);
/**
 * @brief Parse a string to a uuid
 * @param str the string to transform
 * @return the uuid parsed from the string
 */
uuid_t *uuid_from_string(const char *str);
/**
 * @brief Generate a new uuid
 * @return the generated uuid
 */
uuid_t *uuid_generate(void);
