/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** help
*/

#include "myclient.h"

static void help_create(void)
{
    printf("/create\n");
    printf("When the context is not defined (/use):\n");
    printf("/create [“team_name”] [“team_description”] : create a "
        "new team\n");
    printf("When the context is a team (/use [“team_uuid”]):\n");
    printf("/create [“channel_name”] [“channel_description”] : create"
        " a new channel\n");
    printf("When the context is a channel (/use [“team_uuid”] "
        "[“channel_uuid”]):\n");
    printf("/create [“thread_title”] [“thread_body”] : create "
        "a new thread\n");
    printf("When the context is a thread (/use [“team_uuid”] "
        "[“channel_uuid”] [“thread_uuid”]):\n");
    printf("/create [comment_body] : create a new reply\n");
}

static void help_list(void)
{
    printf("/list\n");
    printf("When the context is not defined (/use):\n");
    printf("/list : list all the teams\n");
    printf("When the context is a team (/use [“team_uuid”]):\n");
    printf("/list : list all the channels\n");
    printf("When the context is a channel (/use [“team_uuid”] "
        "[“channel_uuid”]):\n");
    printf("/list : list all the threads\n");
    printf("When the context is a thread (/use [“team_uuid”] "
        "[“channel_uuid”] [“thread_uuid”]):\n");
    printf("/list : list all the replies\n");
}

static void help_info(void)
{
    printf("/info\n");
    printf("When the context is not defined (/use):\n");
    printf("/info : show the details of the currently logged-in user\n");
    printf("When the context is a team (/use [“team_uuid”]):\n");
    printf("/info : show the details of the current team\n");
    printf("When the context is a channel (/use [“team_uuid”] "
        "[“channel_uuid”]):\n");
    printf("/info : show the details of the current channel\n");
    printf("When the context is a thread (/use [“team_uuid”] "
        "[“channel_uuid”] [“thread_uuid”]):\n");
    printf("/info : show the details of the current thread\n");
}

static void help_no_args(void)
{
    printf("Available commands:\n");
    printf("/login [\"user_name\"]\n");
    printf("/logout\n");
    printf("/users\n");
    printf("/user [\"user_uuid\"]\n");
    printf("/send [\"user_uuid\"] [\"message_body\"]\n");
    printf("/messages [\"user_uuid\"]\n");
    printf("/subscribe [\"team_uuid\"]\n");
    printf("/subscribed ?[\"team_uuid\"]\n");
    printf("/unsubscribe [\"team_uuid\"]\n");
    printf("/use ?[\"team_uuid\"] ?[\"channel_uuid\"] ?[\"thread_uuid\"]\n");
    printf("/create\n");
    printf("/list\n");
    printf("/info\n");
    printf("/help\n");
    printf("/exit\n");
}

static void compare_help(char **parsed_cmd)
{
    if (strcmp(parsed_cmd[1], "create") == 0)
        return help_create();
    if (strcmp(parsed_cmd[1], "list") == 0)
        return help_list();
    if (strcmp(parsed_cmd[1], "info") == 0)
        return help_info();
    printf("The command %s either does not exist "
        "or does not have a help page\n", parsed_cmd[1]);
}

void help(char **parsed_cmd, client_t *client)
{
    size_t len = tab_len(parsed_cmd);

    (void)client;
    if (len == 1)
        help_no_args();
    if (len == 2)
        compare_help(parsed_cmd);
    if (len > 2)
        printf("Too many arguments for /help\n");
}
