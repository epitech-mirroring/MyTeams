/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

roundtable_thread_t *roundtable_thread_create(const char *title,
    const char *message, roundtable_channel_t *channel)
{
    roundtable_thread_t *thread = malloc(sizeof(roundtable_thread_t));

    if (thread == NULL)
        return NULL;
    COPY_UUID(thread->uuid, *uuid_generate());
    thread->title = strdup(title);
    thread->message_count = 0;
    thread->content = strdup(message);
    thread->created_at = time(NULL);
    thread->messages = NULL;
    roundtable_channel_add_thread(channel, thread);
    return thread;
}

roundtable_thread_t *roundtable_thread_find_by_uuid(
    roundtable_channel_t *channel, uuid_t uuid)
{
    for (size_t i = 0; i < channel->thread_count; i++) {
        if (uuid_compare(channel->threads[i].uuid, uuid) == true)
            return &channel->threads[i];
    }
    return NULL;
}

roundtable_thread_t *get_thread_from_string(roundtable_channel_t *channel,
    char *uuid)
{
    return roundtable_thread_find_by_uuid(channel,
        *uuid_from_string(uuid));
}

roundtable_thread_t *get_thread_from_json(roundtable_channel_t *channel,
    json_object_t *body, char *key)
{
    return roundtable_thread_find_by_uuid(channel,
        *uuid_from_string(((json_string_t *)
        json_object_get(body, key))->value));
}
