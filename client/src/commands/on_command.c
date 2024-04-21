/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** on_command
*/

#include "myclient.h"
#include "commands.h"

const command_t commands[] = {
    {"/help", &help},
    {"/login", &login},
    {"/logout", &logout},
    {"/user", &user},
    {"/users", &users},
    {"/send", &cmd_send},
    {"/messages", &messages},
    {"/subscribe", &subscribe},
    {"/subscribed", &subscribed},
    {"/unsubscribe", &unsubscribe},
    {"/use", &use},
    {"/create", &create},
    {"/list", &list},
    {"/info", &info},
    {NULL, NULL}
};

void on_command(char *cmd, client_t *client)
{
    char **parsed_cmd = parse_command(cmd);

    if (parsed_cmd == NULL)
        return;
    for (int i = 0; commands[i].cmd != NULL; i++) {
        if (strcmp(parsed_cmd[0], commands[i].cmd) == 0) {
            commands[i].func(parsed_cmd, client);
            return;
        }
    }
    printf("Unknown command\n");
}
