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

char *add_bearer(const char *uuid, size_t instance_id)
{
    char *instance_id_str = calloc(11, sizeof(char));
    char *bearer = calloc((strlen(uuid) + 8 + 11), sizeof(char));

    if (instance_id_str == NULL || bearer == NULL)
        return NULL;
    sprintf(instance_id_str, "%ld", instance_id);
    strcpy(bearer, "Bearer ");
    strcat(bearer, uuid);
    strcat(bearer, "_");
    strcat(bearer, instance_id_str);
    return bearer;
}
