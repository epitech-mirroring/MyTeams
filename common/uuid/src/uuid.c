/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "uuid/uuid.h"

bool uuid_compare(const uuid_t uu1, const uuid_t uu2)
{
    for (int i = 0; i < 16; i++)
        if (uu1[i] != uu2[i])
            return false;
    return true;
}
