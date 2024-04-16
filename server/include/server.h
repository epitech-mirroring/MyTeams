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

#define COPY_UUID(dest, src) memcpy(dest, src, 16)

void save_data(roundtable_server_t *server);
json_array_t *serialize_clients(roundtable_server_t *server);
json_object_t *serialize_client(roundtable_client_t *client);
json_array_t *serialize_teams(roundtable_server_t *server);
json_object_t *serialize_team(roundtable_team_t *team);
json_array_t *serialize_channels(roundtable_server_t *server);
json_object_t *serialize_channel(roundtable_channel_t *channel);
json_array_t *serialize_threads(roundtable_server_t *server);
json_object_t *serialize_thread(roundtable_thread_t *thread);
json_array_t *serialize_messages(roundtable_server_t *server);
json_object_t *serialize_message(roundtable_message_t *message);
json_array_t *serialize_subscribers(roundtable_server_t *server);
json_array_t *serialize_direct_messages(roundtable_server_t *server);
void load_data(roundtable_server_t *server, const char *path);
void deserialize_clients(roundtable_server_t *server, json_array_t *clients);
void deserialize_client(roundtable_server_t *server, json_object_t *client);
void deserialize_teams(roundtable_server_t *server, json_array_t *teams);
void deserialize_team(roundtable_server_t *server, json_object_t *team);
void deserialize_channels(json_array_t *channels, roundtable_team_t *team);
void deserialize_channel(json_object_t *channel, roundtable_team_t *team);
void deserialize_threads(json_array_t *threads, roundtable_channel_t *channel);
void deserialize_thread(json_object_t *thread, roundtable_channel_t *channel);
void deserialize_messages(json_array_t *messages, roundtable_thread_t *thread);
void deserialize_message(json_object_t *message, roundtable_thread_t *thread);
void deserialize_subscribers(roundtable_server_t *server,
    json_array_t *subscribers, roundtable_team_t *team);
void deserialize_direct_messages(roundtable_server_t *server,
    json_array_t *direct_messages);
void deserialize_direct_message(roundtable_server_t *server,
    json_object_t *message);
void deserialize_direct_message_messages(json_array_t *messages,
    roundtable_direct_message_t *direct_message);
void deserialize_direct_message_message(json_object_t *message,
    roundtable_direct_message_t *direct_message);
void roundtable_server_add_client(roundtable_server_t *server,
    roundtable_client_t *client);
void roundtable_server_add_team(roundtable_server_t *server,
    roundtable_team_t *team);
void roundtable_team_add_channel(roundtable_team_t *team,
    roundtable_channel_t *channel);
void roundtable_channel_add_thread(roundtable_channel_t *channel,
    roundtable_thread_t *thread);
void roundtable_thread_add_message(roundtable_thread_t *thread,
    roundtable_message_t *message);
void roundtable_server_add_direct_message(roundtable_server_t *server,
    roundtable_direct_message_t *direct_message);
void roundtable_team_add_subscriber(roundtable_team_t *team,
    roundtable_client_t *subscriber);
void roundtable_direct_message_add_message(
    roundtable_direct_message_t *direct_message,
    roundtable_message_t *message);

roundtable_client_t *roundtable_server_get_client_by_uuid(
    roundtable_server_t *server, uuid_t uuid);
