/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <stddef.h>
#include <string.h>
#include "uuid/uuid.h"
#include "network/router.h"
#include <time.h>

/**
 * @brief Copy a UUID from src to dest
 * @note This is a macro because the uuid_t type is an array of 16unsigned char
 */
#define COPY_UUID(dest, src) uuid_copy(dest, src)

/**
 * @brief A message sent by a client in a thread or a direct message
 */
typedef struct roundtable_message_s {
    uuid_t sender_uuid;
    time_t created_at;
    char *content;
} roundtable_message_t;

/**
 * @brief A thread in a channel
 */
typedef struct roundtable_thread_s {
    uuid_t uuid;
    char *title;
    char *content;
    roundtable_message_t *messages;
    size_t message_count;
    time_t created_at;
} roundtable_thread_t;

/**
 * @brief A channel in a team
 * @note A channel can have multiple threads
 */
typedef struct roundtable_channel_s {
    uuid_t uuid;
    char *name;
    char *description;
    roundtable_thread_t *threads;
    size_t thread_count;
} roundtable_channel_t;

/**
 * @brief A direct message between two clients
 */
typedef struct roundtable_direct_message_s {
    uuid_t sender_uuid;
    uuid_t receiver_uuid;
    roundtable_message_t *messages;
    size_t message_count;
} roundtable_direct_message_t;

/**
 * @brief The status of a client
 */
typedef enum roundtable_status_s {
    ONLINE,
    OFFLINE,
    AWAY,
    BUSY
} roundtable_status_t;

/**
 * @brief A client registered in the server
 */
typedef struct roundtable_client_s {
    uuid_t uuid;
    char *username;
    roundtable_status_t status;
} roundtable_client_t;

/**
 * @brief A team in the server
 * @note A team can have multiple channels and subscribers
 */
typedef struct roundtable_team_s {
    uuid_t uuid;
    char *name;
    char *description;
    roundtable_channel_t *channels;
    size_t channel_count;
    uuid_t *subscribers;
    size_t subscriber_count;
} roundtable_team_t;

/**
 * @brief The server containing all the data
 */
typedef struct roundtable_server_s {
    roundtable_team_t *teams;
    size_t team_count;
    roundtable_client_t *clients;
    size_t client_count;
    roundtable_direct_message_t **direct_messages;
    size_t message_count;
    router_t *router;
} roundtable_server_t;
