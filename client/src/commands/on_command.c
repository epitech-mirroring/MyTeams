/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** on_command
*/

#include "myclient.h"

void on_command_2(char **parsed_cmd, client_t *client)
{
    if (strcmp(parsed_cmd[0], "/subscribe") == 0)
        return subscribe(parsed_cmd, client);
    printf("Unknown command\n");
}

void on_command(char *cmd, client_t *client)
{
    char **parsed_cmd = parse_command(cmd);

    if (parsed_cmd == NULL)
        return;
    if (strcmp(parsed_cmd[0], "/help") == 0)
        return help(parsed_cmd);
    if (strcmp(parsed_cmd[0], "/login") == 0)
        return login(parsed_cmd, client);
    if (strcmp(parsed_cmd[0], "/logout") == 0)
        return logout(parsed_cmd, client);
    if (strcmp(parsed_cmd[0], "/user") == 0)
        return user(parsed_cmd, client);
    if (strcmp(parsed_cmd[0], "/users") == 0)
        return users(parsed_cmd, client);
    if (strcmp(parsed_cmd[0], "/send") == 0)
        return cmd_send(parsed_cmd, client);
    if (strcmp(parsed_cmd[0], "/messages") == 0)
        return messages(parsed_cmd, client);
    return on_command_2(parsed_cmd, client);
}
