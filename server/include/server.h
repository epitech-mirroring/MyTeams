/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "server_types.h"
#include "json/json.h"

// --------------------------- SERVER CONSTRUCTORS -------------------------
/**
 * @brief Create an empty server
 * @param port the port to listen on
 * @return the newly created server or NULL if an error occurred
 */
roundtable_server_t *create_server(int port);
// --------------------------- SERVER ROUTER -------------------------------
typedef struct roundtable_route_s {
    char *path;
    response_t (*handler)(request_t *req, void *data);
} roundtable_route_t;
extern const roundtable_route_t ROUTES[];
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
void destroy_client(roundtable_client_t *client);
/**
 * @brief Destroy a team (including all channels) and free its memory
 * @param team the team to destroy
 */
void destroy_team(roundtable_team_t *team);
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
 * @brief Get a client by its username
 * @param server The server to search in
 * @param username The username of the client to find
 * @return The client if found, NULL otherwise
 */
roundtable_client_t *roundtable_server_get_client_by_username(
    roundtable_server_t *server, const char *username);
/**
 * @brief Add a client to the server
 * @param server The server to add the client to
 * @param client The client to add
 */
void roundtable_server_add_client(roundtable_server_t *server,
    roundtable_client_t *client);
/**
 * @brief Create a client
 * @param server The server to create the client in
 * @param username The username of the client
 * @return The newly created client or NULL if an error occurred
 */
roundtable_client_t *roundtable_server_create_client(
    roundtable_server_t *server, const char *username);
/**
 * @brief Get a client from a request authorization header
 * @param server The server to search in
 * @param request The request to get the client from
 * @return The client if found, NULL otherwise (no header, not a valid UUID)
 */
roundtable_client_t *get_client_from_header(
    roundtable_server_t *server, request_t *request);
/**
 * @brief Get a client from a json object
 * @param server The server to search in
 * @param body the json object to search in
 * @param key the key of the client to find
 * @return The client if found, NULL otherwise
 */
roundtable_client_t *get_client_from_json(
    roundtable_server_t *server, json_object_t *body, char *key);
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
/**
 * @brief Create a team
 * @param server The server to create the team in
 * @param name the name of the team
 * @param description the description of the team
 * @return The newly created team or NULL if an error occurred
 */
roundtable_team_t *roundtable_server_create_team(
    roundtable_server_t *server, const char *name, const char *description);
/**
 * @brief Get a team by its UUID
 * @param server The server to search in
 * @param uuid The UUID of the team to find
 * @return The team if found, NULL otherwise
 */
roundtable_team_t *roundtable_server_get_team_by_uuid(
    roundtable_server_t *server, uuid_t uuid);
/**
 * @brief Check if a client is a subscriber of a team
 * @param team the team to check in
 * @param client the client to check for
 * @return true if the client is a subscriber, false otherwise
 */
bool roundtable_team_has_subscriber(roundtable_team_t *team,
    roundtable_client_t *client);
/**
 * @brief Get a team from a json object
 * @param server The server to search in
 * @param body The json object to search in
 * @param key The key of the team to find
 * @return The team if found, NULL otherwise
 */
roundtable_team_t *get_team_from_json(roundtable_server_t *server,
    json_object_t *body, char *key);
/**
 * @brief Remove a subscriber from a team
 * @param team The team to remove the subscriber from
 * @param subscriber The subscriber to remove
 */
void roundtable_team_remove_subscriber(roundtable_team_t *team,
    roundtable_client_t *subscriber);
/**
 * @brief Get a team from a string
 * @param server The server to search in
 * @param uuid_str The string representation of the team's UUID
 * @return The team if found, NULL otherwise
 */
roundtable_team_t *get_team_from_string(
    roundtable_server_t *server, char *uuid_str);
// --------------------------- SERVER CHANNELS -----------------------------
/**
 * @brief Add a thread to a channel
 * @param channel The channel to add the thread to
 * @param thread The thread to add
 */
void roundtable_channel_add_thread(roundtable_channel_t *channel,
    roundtable_thread_t *thread);
/**
 * @brief Create a channel
 * @param name The name of the channel
 * @param description The description of the channel
 * @param team The team the channel belongs to
 * @return The newly created channel or NULL if an error occurred
 * @note The channel is automatically added to the team
 */
roundtable_channel_t *roundtable_channel_create(const char *name,
    const char *description, roundtable_team_t *team);

/**
 * @brief Get a channel by its UUID
 * @param team the team the channel belongs to
 * @param uuid the UUID of the channel to find
 * @return The channel if found, NULL otherwise
 * @note The channel must belong to the team
 */
roundtable_channel_t *roundtable_channel_find_by_uuid(roundtable_team_t *team,
    uuid_t uuid);

/**
 * @brief Get a channel from a json object
 * @param team The team to search in
 * @param body The json object to search in
 * @param key The key of the channel to find
 * @return The channel if found, NULL otherwise
 * @note The channel must belong to the team
 */
roundtable_channel_t *get_channel_from_json(roundtable_team_t *team,
    json_object_t *body, char *key);

// --------------------------- SERVER THREADS ------------------------------
/**
 * @brief Add a message to a thread
 * @param thread The thread to add the message to
 * @param message The message to add
 */
void roundtable_thread_add_message(roundtable_thread_t *thread,
    roundtable_message_t *message);
/**
 * @brief Create a thread
 * @param name The name of the thread
 * @param channel The channel the thread belongs to
 * @return The newly created thread or NULL if an error occurred
 * @note The thread is automatically added to the channel
 */
roundtable_thread_t *roundtable_thread_create(const char *title,
    const char *message, roundtable_channel_t *channel,
    roundtable_client_t *sender);

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
/**
 * @brief Find a direct message between two clients
 * @param server The server to search in
 * @param sender the sender of the message
 * @param receiver the receiver of the message
 * @return The direct message if found, NULL otherwise
 * @note Sender is not necessarily the sender of the direct message since
 * direct messages are bidirectional
 */
roundtable_direct_message_t *roundtable_server_find_direct_message(
    roundtable_server_t *server, roundtable_client_t *sender,
    roundtable_client_t *receiver);
/**
 * @brief Create a direct message between two clients
 * @param sender The sender of the initial message
 * @param receiver The receiver of the initial message
 * @return The newly created direct message or NULL if an error occurred
 */
roundtable_direct_message_t *roundtable_direct_message_create(
    roundtable_client_t *sender, roundtable_client_t *receiver);
/**
 * @brief Create a message
 * @param sender The sender of the message
 * @param message The message to send
 * @return The newly created message or NULL if an error occurred
 */
roundtable_message_t *roundtable_message_create(roundtable_client_t *sender,
    json_object_t *message);
/**
 * @brief Send a direct message between two clients
 * @param server The server to send the message in
 * @param sender The sender of the message
 * @param receiver The receiver of the message
 * @param message
 */
void roundtable_server_send_dm(roundtable_server_t *server,
    roundtable_client_t *sender, roundtable_client_t *receiver,
    json_object_t *message);
/**
 * @brief Get a direct message from a json object
 * @param server The server to search in
 * @param body The json object to search in
 * @param key The key of the direct message to find
 * @return The direct message if found, NULL otherwise
 */
roundtable_thread_t *roundtable_thread_find_by_uuid(
    roundtable_channel_t *channel, uuid_t uuid);
/**
 *  @brief Get a thread from a string
 *  @param channel The channel to search in
 *  @param uuid The string representation of the thread's UUID
 *  @return The thread if found, NULL otherwise
 */
roundtable_thread_t *get_thread_from_string(roundtable_channel_t *channel,
    char *uuid);

/**
 * @brief Create a reply to a message
 * @param content The content of the reply
 * @param sender The sender of the reply
 * @return The newly created reply or NULL if an error occurred
 */
roundtable_message_t *roundtable_reply_create(const char *content,
    roundtable_client_t *sender, roundtable_thread_t *thread);
/**
 * @brief Get a thread from a json object
 * @param channel The channel to search in
 * @param body The json object to search in
 * @param key The key of the thread to find
 * @return The thread if found, NULL otherwise
 */
roundtable_thread_t *get_thread_from_json(roundtable_channel_t *channel,
    json_object_t *body, char *key);
