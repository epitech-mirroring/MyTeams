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
#include "json/json.h"

#define _GNU_SOURCE

#define MAX_NUM_ARGS 4
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

enum client_event {
    LOGGED_IN,
    LOGGED_OUT,
    DM_RECEIVED,
    TEAM_CREATED,
    CHANNEL_CREATED,
    THREAD_CREATED,
    THREAD_REPLIED,
    NONE,
};

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
    bool running;
    bool is_event;
    char *buffer;
    api_client_t *api_handler;
} client_t;

typedef struct event_bindig_s {
    enum client_event event;
    void (*callback)(json_object_t *data, client_t *client);
} event_binding_t;

extern const event_binding_t event_bindings[];

int client(int ac, char **av);

int is_valid_args(int ac, char **av);
void print_help(void);

void on_command(char *cmd, client_t *client);
char **parse_command(char *cmd);

size_t tab_len(char **tab);
char *add_bearer(const char *uuid);
void logout_when_leaving(client_t *client);

void help(char **parsed_cmd);
void logout(char **parsed_cmd, client_t *client);
void login(char **parsed_cmd, client_t *client);
void user(char **parsed_cmd, client_t *client);
void users(char **parsed_cmd, client_t *client);
void cmd_send(char **parsed_cmd, client_t *client);
void messages(char **parsed_cmd, client_t *client);
void subscribe(char **parsed_cmd, client_t *client);
void subscribed(char **parsed_cmd, client_t *client);
void unsubscribe(char **parsed_cmd, client_t *client);
void use(char **parsed_cmd, client_t *client);

void create(char **parsed_cmd, client_t *client);
void create_team(char **parsed_cmd, client_t *client);
void create_channel(char **parsed_cmd, client_t *client);
void create_thread(char **parsed_cmd, client_t *client);
void create_reply(char **parsed_cmd, client_t *client);

void send_events(client_t *client);
void logged_in_callback(json_object_t *data, client_t *client);
void logged_out_callback(json_object_t *data, client_t *client);
void dm_received_callback(json_object_t *data, client_t *client);
void team_created_callback(json_object_t *data, client_t *client);
void channel_created_callback(json_object_t *data, client_t *client);
