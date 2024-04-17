/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** utils
*/

#include "myclient.h"

int tab_len(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    return i;
}
