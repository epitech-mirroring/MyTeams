/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** parsing
*/

#include "myclient.h"

static void skip_spaces(char *cmd, int *index)
{
    while (cmd[*index] != '\0' && cmd[*index] == ' ')
        (*index)++;
}

static char *argument_part(char *cmd, int *index)
{
    char *argument = NULL;
    size_t i = 0;

    if (cmd[*index] != '"') {
        printf("Error: argument must be between double quotes\n");
        return NULL;
    }
    (*index)++;
    for (i = *index; cmd[i] != '\0' && cmd[i] != '"'; i++);
    if (cmd[i] == '\0') {
        printf("Error: argument must be between double quotes\n");
        return NULL;
    }
    argument = strndup(&cmd[*index], i - *index);
    if (argument == NULL) {
        return NULL;
    }
    *index = i + 1;
    return argument;
}

static char *command_part(char *cmd, int *index)
{
    char *command = NULL;
    size_t i = 0;

    for (i = *index; cmd[i] != '\0' && cmd[i] != '\n' && cmd[i] != ' '; i++);
    command = strndup(&cmd[*index], i - *index);
    if (command == NULL) {
        return NULL;
    }
    *index = i;
    return command;
}

void print_parsed_command(char **parsed_cmd)
{
    for (int i = 0; parsed_cmd[i] != NULL; i++) {
        printf("parsed_cmd[%d] = '%s'\n", i, parsed_cmd[i]);
    }
}

static bool parse_loop(char *cmd, int *index, char **parsed_cmd, int i)
{
    skip_spaces(cmd, index);
    if (cmd[*index] != '\0' && cmd[*index] != '\n') {
        parsed_cmd[i] = argument_part(cmd, index);
        if (parsed_cmd[i] == NULL)
            return false;
    }
    return true;
}

char **parse_command_2(char *cmd, int *index, char **parsed_cmd)
{
    for (size_t i = 1; i < MAX_NUM_ARGS; i++) {
        if (!parse_loop(cmd, index, parsed_cmd, i))
            return NULL;
    }
    skip_spaces(cmd, index);
    if (cmd[*index] != '\0' && cmd[*index] != '\n') {
        printf("Error: too many arguments\n");
        return NULL;
    }
    parsed_cmd[MAX_NUM_ARGS] = NULL;
    return parsed_cmd;
}

char **parse_command(char *cmd)
{
    char **parsed_cmd = calloc(MAX_NUM_ARGS + 1, sizeof(char *));
    size_t index = 0;

    if (parsed_cmd == NULL || cmd == NULL) {
        return NULL;
    }
    skip_spaces(cmd, &index);
    if (cmd[index] != '\0') {
        parsed_cmd[0] = command_part(cmd, &index);
        if (parsed_cmd[0] == NULL)
            return NULL;
    }
    return parse_command_2(cmd, &index, parsed_cmd);
}
