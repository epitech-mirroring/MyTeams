/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once

#include <stddef.h>
#include "uuid/uuid.h"

typedef struct roundtable_message_s {
    uuid_t sender_uuid;
    char *content;
} roundtable_message_t;

typedef struct roundtable_thread_s {
    uuid_t uuid;
    char *title;
    char *content;
    roundtable_message_t *messages;
    size_t message_count;
} roundtable_thread_t;

typedef struct roundtable_channel_s {
    uuid_t uuid;
    char *name;
    char *description;
    roundtable_thread_t *threads;
    size_t thread_count;
} roundtable_channel_t;

typedef struct roundtable_direct_message_s {
    uuid_t sender_uuid;
    uuid_t receiver_uuid;
    roundtable_message_t *messages;
    size_t message_count;
} roundtable_direct_message_t;

typedef enum roundtable_status_s {
    ONLINE,
    OFFLINE,
    AWAY,
    BUSY
} roundtable_status_t;

typedef struct roundtable_client_s {
    uuid_t uuid;
    char *username;
    roundtable_status_t status;
} roundtable_client_t;

typedef struct roundtable_team_s {
    uuid_t uuid;
    char *name;
    char *description;
    roundtable_channel_t *channels;
    size_t channel_count;
    uuid_t *subscribers;
    size_t subscriber_count;
} roundtable_team_t;

typedef struct roundtable_server_s {
    roundtable_team_t *teams;
    size_t team_count;
    roundtable_client_t *clients;
    size_t client_count;
    roundtable_direct_message_t *direct_messages;
    size_t message_count;
} roundtable_server_t;
