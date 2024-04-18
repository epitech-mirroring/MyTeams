/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "uuid/uuid.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

bool uuid_compare(const uuid_t uu1, const uuid_t uu2)
{
    for (size_t i = 0; i < 16; i++)
        if (uu1[i] != uu2[i])
            return false;
    return true;
}

char *uuid_to_string(const uuid_t uu)
{
    char *str = malloc(37);

    if (!str)
        return NULL;
    for (size_t i = 0; i < 16; i++) {
        sprintf(&str[i * 2], "%02x", uu[i]);
    }
    str[36] = '\0';
    return str;
}

uuid_t *uuid_from_string(const char *str)
{
    uuid_t *uu = malloc(16);
    unsigned char byte;

    if (!uu || !str || strlen(str) != 32) {
        free(uu);
        return NULL;
    }
    for (size_t i = 0; i < 16; i++) {
        if (sscanf(&str[i * 2], "%2hhx", &byte) != 1) {
            free(uu);
            return NULL;
        }
        (*uu)[i] = byte;
    }
    return uu;
}

uuid_t *uuid_generate(void)
{
    uuid_t *uu = malloc(16);

    srand(time(NULL));
    if (!uu)
        return NULL;
    for (size_t i = 0; i < 16; i++)
        (*uu)[i] = rand() % 256;
    return uu;
}

void uuid_copy(uuid_t dest, const uuid_t src)
{
    for (size_t i = 0; i < 16; i++)
        dest[i] = src[i];
}
