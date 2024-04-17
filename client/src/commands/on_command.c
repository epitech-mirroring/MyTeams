/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** on_command
*/

#include "myclient.h"

void on_command(char *cmd, client_t *client)
{
    char **parsed_cmd = parse_command(cmd);

    if (parsed_cmd == NULL)
        return;
    if (strcmp(parsed_cmd[0], "/help") == 0)
        return help(parsed_cmd);
    printf("Unknown command\n");
}
