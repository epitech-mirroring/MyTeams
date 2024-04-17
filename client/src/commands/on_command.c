/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** on_command
*/

#include "myclient.h"

// void on_command(char *cmd, client_t *client)
// {
//     char **parsed_cmd = parse_command(cmd);

//     if (parsed_cmd == NULL)
//         return;
//     if (strcmp(parsed_cmd[0], "/help") == 0)
//         return help(parsed_cmd);
//     if (strcmp(parsed_cmd[0], "/login") == 0)
//         return login(parsed_cmd, client);
//     if (strcmp(parsed_cmd[0], "/logout") == 0)
//         return logout(parsed_cmd, client);
//     if (strcmp(parsed_cmd[0], "/users") == 0)
//         printf("Users command\n");
//     if (strcmp(parsed_cmd[0], "/user") == 0)
//         printf("User command\n");
//     if (strcmp(parsed_cmd[0], "/send") == 0)
//         printf("Send command\n");
//     if (strcmp(parsed_cmd[0], "/messages") == 0)
//         printf("Messages command\n");
//     if (strcmp(parsed_cmd[0], "/subscribe") == 0)
//         printf("Subscribe command\n");
//     if (strcmp(parsed_cmd[0], "/subscribed") == 0)
//         printf("Subscribed command\n");
//     if (strcmp(parsed_cmd[0], "/unsubscribe") == 0)
//         printf("Unsubscribe command\n");
//     printf("Unknown command\n");
// }


void on_command(char *cmd, client_t *client)
{
    char **parsed_cmd = parse_command(cmd);

    if (parsed_cmd == NULL)
        return;
    if (strcmp(parsed_cmd[0], "/help") == 0)
        return help(parsed_cmd);
    printf("Unknown command\n");
}
