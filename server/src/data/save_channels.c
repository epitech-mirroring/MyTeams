/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server_data.h"

json_object_t *serialize_channel(roundtable_channel_t *channel)
{
    json_object_t *json = json_object_create(NULL);
    json_string_t *uuid = json_string_create("uuid",
        uuid_to_string(channel->uuid));
    json_string_t *name = json_string_create("name", channel->name);
    json_string_t *description = json_string_create("description",
        channel->description);
    json_array_t *threads = serialize_threads(channel);

    json_object_add(json, (json_t *) uuid);
    json_object_add(json, (json_t *) name);
    json_object_add(json, (json_t *) description);
    json_object_add(json, (json_t *) threads);
    return json;
}

json_array_t *serialize_threads(roundtable_channel_t *channel)
{
    json_array_t *threads = json_array_create("threads");

    for (size_t i = 0; i < channel->thread_count; i++) {
        json_array_add(threads,
            (json_t *) serialize_thread(&channel->threads[i]));
    }
    return threads;
}
