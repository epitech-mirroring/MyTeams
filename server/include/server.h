/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "server_types.h"

// --------------------------- SERVER CONSTRUCTORS -------------------------
/**
 * @brief Create an empty server
 * @return the newly created server or NULL if an error occurred
 */
roundtable_server_t *create_server(void);
// --------------------------- SERVER DESTRUCTORS --------------------------
/**
 * @brief Destroy a server (including all clients, teams, channels,
 * threads and messages) and free its memory
 * @param server the server to destroy
 */
void destroy_server(roundtable_server_t *server);
/**
 * @brief Destroy a client and free its memory
 * @param client the client to destroy
 */
void destroy_client(roundtable_client_t client);
/**
 * @brief Destroy a team (including all channels) and free its memory
 * @param team the team to destroy
 */
void destroy_team(roundtable_team_t team);
/**
 * @brief Destroy a message and free its memory
 * @param message
 */
void destroy_message(roundtable_message_t message);
/**
 * @brief Destroy a channel (including all threads) and free its memory
 * @param channel the channel to destroy
 */
void destroy_channel(roundtable_channel_t channel);
/**
 * @brief Destroy a thread (including all messages) and free its memory
 * @param thread the thread to destroy
 */
void destroy_thread(roundtable_thread_t thread);
// --------------------------- SERVER CLIENTS ------------------------------
/**
 * @brief Get a client by its UUID
 * @param server The server to search in
 * @param uuid The UUID of the client to find
 * @return The client if found, NULL otherwise
 */
roundtable_client_t *roundtable_server_get_client_by_uuid(
    roundtable_server_t *server, uuid_t uuid);
/**
 * @brief Add a client to the server
 * @param server The server to add the client to
 * @param client The client to add
 */
void roundtable_server_add_client(roundtable_server_t *server,
    roundtable_client_t *client);
// --------------------------- SERVER TEAMS --------------------------------
/**
 * @brief Add a team to the server
 * @param server The server to add the team to
 * @param team The team to add
 */
void roundtable_server_add_team(roundtable_server_t *server,
    roundtable_team_t *team);
/**
 * @brief Add a channel to a team
 * @param team The team to add the channel to
 * @param channel The channel to add
 */
void roundtable_team_add_channel(roundtable_team_t *team,
    roundtable_channel_t *channel);
/**
 * @brief Add a subscriber to a team
 * @param team The team to add the subscriber to
 * @param subscriber The subscriber to add
 */
void roundtable_team_add_subscriber(roundtable_team_t *team,
    roundtable_client_t *subscriber);
// --------------------------- SERVER CHANNELS -----------------------------
/**
 * @brief Add a thread to a channel
 * @param channel The channel to add the thread to
 * @param thread The thread to add
 */
void roundtable_channel_add_thread(roundtable_channel_t *channel,
    roundtable_thread_t *thread);
// --------------------------- SERVER THREADS ------------------------------
/**
 * @brief Add a message to a thread
 * @param thread The thread to add the message to
 * @param message The message to add
 */
void roundtable_thread_add_message(roundtable_thread_t *thread,
    roundtable_message_t *message);
// ---------------------- SERVER DIRECT MESSAGES ---------------------------
/**
 * @brief Add a direct message to the server
 * @param server The server to add the direct message to
 * @param direct_message The direct message to add
 */
void roundtable_server_add_direct_message(roundtable_server_t *server,
    roundtable_direct_message_t *direct_message);
/**
 * @brief Add a message to a direct message
 * @param direct_message The direct message to add the message to
 * @param message The message to add
 */
void roundtable_direct_message_add_message(
        roundtable_direct_message_t *direct_message,
        roundtable_message_t *message);