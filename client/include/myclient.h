/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** myclient
*/

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/select.h>
#include <signal.h>
#include "uuid/uuid.h"
#include "network/api_client.h"
#include "network/dto.h"

#define _GNU_SOURCE

#define MAX_NUM_ARGS 4
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

typedef struct context_s {
    char const *team_uuid;
    char const *channel_uuid;
    char const *thread_uuid;
} context_t;

typedef struct client_s {
    context_t *context;
    char const *user_uuid;
    char const *user_name;
    bool is_logged;
    bool waiting_for_response;
    api_client_t *api_handler;
} client_t;

int client(int ac, char **av);

int is_valid_args(int ac, char **av);
void print_help(void);

void on_command(char *cmd, client_t *client);
char **parse_command(char *cmd);

size_t tab_len(char **tab);
char *add_bearer(char *uuid);


void help(char **parsed_cmd);
void logout(char **parsed_cmd, client_t *client);
void login(char **parsed_cmd, client_t *client);
void user(char **parsed_cmd, client_t *client);
void users(char **parsed_cmd, client_t *client);
void cmd_send(char **parsed_cmd, client_t *client);
void messages(char **parsed_cmd, client_t *client);
void subscribe(char **parsed_cmd, client_t *client);
