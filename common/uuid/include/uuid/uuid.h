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
