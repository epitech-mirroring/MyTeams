/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** utils
*/

#include "myclient.h"

int tab_len(char **tab)
{
    size_t i = 0;

    while (tab[i] != NULL)
        i++;
    return i;
}
