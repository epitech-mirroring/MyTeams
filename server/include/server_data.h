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

/**
 * @brief Save the server data to a file
 * @param server The server to save
 * @param path The path to save the data to
 */
void save_data(roundtable_server_t *server, const char *path);
/**
 * @brief Serialize the server data to a json object
 * @param server The server to serialize
 * @return The serialized server data
 */
json_array_t *serialize_clients(roundtable_server_t *server);
/**
 * @brief Serialize a client to a json object
 * @param client The client to serialize
 * @return The serialized client data
 */
json_object_t *serialize_client(roundtable_client_t *client);
/**
 * @brief Serialize the teams of a server to a json array
 * @param server The server to serialize
 * @return The serialized teams
 */
json_array_t *serialize_teams(roundtable_server_t *server);
/**
 * @brief Serialize a team to a json object
 * @param team The team to serialize
 * @return The serialized team data
 */
json_object_t *serialize_team(roundtable_team_t *team);
/**
 * @brief Serialize the channels of a team to a json array
 * @param team The team to serialize its channels
 * @return The serialized channels
 */
json_array_t *serialize_channels(roundtable_team_t *team);
/**
 * @brief Serialize a channel to a json object
 * @param channel The channel to serialize
 * @return The serialized channel data
 */
json_object_t *serialize_channel(roundtable_channel_t *channel);
/**
 * @brief Serialize the threads of a channel to a json array
 * @param channel The channel to serialize its threads
 * @return The serialized threads
 */
json_array_t *serialize_threads(roundtable_channel_t *channel);
/**
 * @brief Serialize a thread to a json object
 * @param thread The thread to serialize
 * @return The serialized thread data
 */
json_object_t *serialize_thread(roundtable_thread_t *thread);
/**
 * @brief Serialize a list of messages to a json array
 * @param messages The messages to serialize
 * @param message_count The number of messages
 * @return The serialized messages
 */
json_array_t *serialize_messages(roundtable_message_t *messages,
    size_t message_count);
/**
 * @brief Serialize a message to a json object
 * @param message The message to serialize
 * @return The serialized message data
 */
json_object_t *serialize_message(roundtable_message_t *message);
/**
 * @brief Serialize the subscribers of a team to a json array
 * @param team The team to serialize its subscribers
 * @return The serialized subscribers
 */
json_array_t *serialize_subscribers(roundtable_team_t *server);
/**
 * @brief Serialize the direct messages of a server to a json array
 * @param server The server to serialize
 * @return The serialized direct messages
 */
json_array_t *serialize_direct_messages(roundtable_server_t *server);
/**
 * @brief Serialize a direct message to a json object
 * @param direct_message The direct message to serialize
 * @return The serialized direct message data
 */
json_object_t *serialize_direct_message(
    roundtable_direct_message_t *direct_message);
// --------------------------- LOAD ------------------------------
/**
 * @brief Serialize a direct message to a json object
 * @param direct_message The direct message to serialize
 * @return The serialized direct message data
 */
void load_data(roundtable_server_t *server, const char *path);
/**
 * @brief Deserialize the clients of a server
 * @param server The server to deserialize the clients to (will be filled
 * with the clients)
 * @param clients The clients to deserialize
 */
void deserialize_clients(roundtable_server_t *server, json_array_t *clients);
/**
 * @brief Deserialize a client
 * @param server The server to deserialize the client to
 * @param client The client to deserialize
 */
void deserialize_client(roundtable_server_t *server, json_object_t *client);
/**
 * @brief Deserialize the teams of a server
 * @param server The server to deserialize the teams to (will be filled
 * with the teams)
 * @param teams The teams to deserialize
 */
void deserialize_teams(roundtable_server_t *server, json_array_t *teams);
/**
 * @brief Deserialize a team
 * @param server The server to deserialize the team to
 * @param team The team to deserialize
 */
void deserialize_team(roundtable_server_t *server, json_object_t *team);
/**
 * @brief Deserialize the channels of a team
 * @param channels The channels to deserialize
 * @param team The team to add the channels to
 */
void deserialize_channels(json_array_t *channels, roundtable_team_t *team);
/**
 * @brief Deserialize a channel
 * @param channel The channel to deserialize
 * @param team The team to add the channel to
 */
void deserialize_channel(json_object_t *channel, roundtable_team_t *team);
/**
 * @brief Deserialize the threads of a channel
 * @param threads The threads to deserialize
 * @param channel The channel to add the threads to
 */
void deserialize_threads(json_array_t *threads, roundtable_channel_t *channel);
/**
 * @brief Deserialize a thread
 * @param thread The thread to deserialize
 * @param channel The channel to add the thread to
 */
void deserialize_thread(json_object_t *thread, roundtable_channel_t *channel);
/**
 * @brief Deserialize the messages of a thread
 * @param messages The messages to deserialize
 * @param thread The thread to add the messages to
 */
void deserialize_messages(json_array_t *messages, roundtable_thread_t *thread);
/**
 * @brief Deserialize a message
 * @param message The message to deserialize
 * @param thread The thread to add the message to
 */
void deserialize_message(json_object_t *message, roundtable_thread_t *thread);
/**
 * @brief Deserialize the subscribers of a team
 * @param server The server to search the clients in
 * @param subscribers The subscribers to deserialize
 * @param team The team to add the subscribers to
 */
void deserialize_subscribers(roundtable_server_t *server,
    json_array_t *subscribers, roundtable_team_t *team);
/**
 * @brief Deserialize the messages of a direct message
 * @param server The server to add the direct message to
 * @param direct_messages The direct messages to deserialize
 */
void deserialize_direct_messages(roundtable_server_t *server,
    json_array_t *direct_messages);
/**
 * @brief Deserialize a direct message
 * @param server
 * @param message
 */
void deserialize_direct_message(roundtable_server_t *server,
    json_object_t *message);
/**
 * @brief Deserialize the messages of a direct message
 * @param messages the messages to deserialize
 * @param direct_message the direct message to add the messages to
 */
void deserialize_direct_message_messages(json_array_t *messages,
    roundtable_direct_message_t *direct_message);
/**
 * @brief Deserialize a direct message message
 * @param message the message to deserialize
 * @param direct_message the direct message to add the message to
 */
void deserialize_direct_message_message(json_object_t *message,
    roundtable_direct_message_t *direct_message);
