/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <string.h>
#include "server_data.h"
#include "server.h"

void deserialize_team(roundtable_server_t *server, json_object_t *team)
{
    roundtable_team_t *new_team = calloc(1, sizeof(roundtable_team_t));
    json_string_t *uuid = NULL;
    json_string_t *name = NULL;
    json_string_t *description = NULL;
    json_array_t *subscribers = NULL;
    json_array_t *channels = NULL;

    if (new_team == NULL)
        return;
    uuid = (json_string_t *) json_object_get(team, "uuid");
    name = (json_string_t *) json_object_get(team, "name");
    description = (json_string_t *) json_object_get(team, "description");
    subscribers = (json_array_t *) json_object_get(team, "subscribers");
    channels = (json_array_t *) json_object_get(team, "channels");
    COPY_UUID(new_team->uuid, *uuid_from_string(uuid->value));
    new_team->name = strdup(name->value);
    new_team->description = strdup(description->value);
    deserialize_subscribers(server, subscribers, new_team);
    deserialize_channels(channels, new_team);
    roundtable_server_add_team(server, new_team);
}

void deserialize_channels(json_array_t *channels, roundtable_team_t *team)
{
    for (size_t i = 0; i < channels->size; i++) {
        deserialize_channel(
            (json_object_t *) json_array_get(channels, i), team);
    }
}

void deserialize_channel(json_object_t *channel, roundtable_team_t *team)
{
    roundtable_channel_t *new_channel = calloc(1,
        sizeof(roundtable_channel_t));
    json_string_t *uuid = NULL;
    json_string_t *name = NULL;
    json_string_t *description = NULL;
    json_array_t *threads = NULL;

    if (new_channel == NULL)
        return;
    uuid = (json_string_t *) json_object_get(channel, "uuid");
    name = (json_string_t *) json_object_get(channel, "name");
    description = (json_string_t *) json_object_get(channel, "description");
    threads = (json_array_t *) json_object_get(channel, "threads");
    COPY_UUID(new_channel->uuid, *uuid_from_string(uuid->value));
    new_channel->name = strdup(name->value);
    new_channel->description = strdup(description->value);
    deserialize_threads(threads, new_channel);
    roundtable_team_add_channel(team, new_channel);
}

void deserialize_threads(json_array_t *threads, roundtable_channel_t *channel)
{
    for (size_t i = 0; i < threads->size; i++) {
        deserialize_thread(
            (json_object_t *) json_array_get(threads, i), channel);
    }
}

void deserialize_thread(json_object_t *thread, roundtable_channel_t *channel)
{
    roundtable_thread_t *new_thread = calloc(1, sizeof(roundtable_thread_t));
    json_string_t *content = NULL;
    json_array_t *messages = NULL;
    json_number_t *timestamp = NULL;

    if (new_thread == NULL)
        return;
    content = (json_string_t *) json_object_get(thread, "content");
    messages = (json_array_t *) json_object_get(thread, "messages");
    timestamp = (json_number_t *) json_object_get(thread, "timestamp");
    COPY_UUID(new_thread->sender_uuid, *uuid_from_string(
        ((json_string_t *) json_object_get(thread, "sender_uuid"))->value));
    COPY_UUID(new_thread->uuid, *uuid_from_string(
            ((json_string_t *) json_object_get(thread, "uuid"))->value));
    new_thread->title = strdup(((json_string_t *)
        json_object_get(thread, "title"))->value);
    new_thread->content = strdup(content->value);
    new_thread->created_at = timestamp->value;
    deserialize_messages(messages, new_thread);
    roundtable_channel_add_thread(channel, new_thread);
}
