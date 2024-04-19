/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** utils
*/

#include "myclient.h"

size_t tab_len(char **tab)
{
    size_t i = 0;

    while (tab[i] != NULL)
        i++;
    return i;
}

char *add_bearer(const char *uuid)
{
    char *bearer = malloc(sizeof(char) * (strlen(uuid) + 8));

    if (bearer == NULL)
        return NULL;
    strcpy(bearer, "Bearer ");
    strcat(bearer, uuid);
    return bearer;
}
