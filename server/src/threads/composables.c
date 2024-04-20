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
    const char *message, roundtable_channel_t *channel,
    roundtable_client_t *sender)
{
    roundtable_thread_t *thread = malloc(sizeof(roundtable_thread_t));

    if (thread == NULL)
        return NULL;
    COPY_UUID(thread->sender_uuid, sender->uuid);
    COPY_UUID(thread->uuid, *uuid_generate());
    thread->title = strdup(title);
    thread->message_count = 0;
    thread->content = strdup(message);
    thread->created_at = time(NULL);
    thread->messages = NULL;
    thread->channel = channel;
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

roundtable_message_t *roundtable_reply_create(const char *content,
    roundtable_client_t *sender, roundtable_thread_t *thread)
{
    roundtable_message_t *message = malloc(sizeof(roundtable_message_t));

    if (message == NULL)
        return NULL;
    COPY_UUID(message->sender_uuid, sender->uuid);
    message->content = strdup(content);
    message->created_at = time(NULL);
    roundtable_thread_add_message(thread, message);
    return message;
}

roundtable_thread_t *get_thread_from_string(roundtable_channel_t *channel,
    char *uuid)
{
    uuid_t *uuid_parsed = uuid_from_string(uuid);

    if (uuid_parsed == NULL)
        return NULL;
    return roundtable_thread_find_by_uuid(channel, uuid_parsed);
}

roundtable_thread_t *get_thread_from_json(roundtable_channel_t *channel,
    json_object_t *body, char *key)
{
    char *uuid_str = NULL;
    json_t *uuid_json = json_object_get(body, key);

    if (uuid_json == NULL || uuid_json->type != JSON_OBJECT_TYPE_STRING)
        return NULL;
    uuid_str = ((json_string_t *) uuid_json)->value;
    if (uuid_str == NULL || !uuid_from_string(uuid_str))
        return NULL;
    return roundtable_thread_find_by_uuid(channel,
        *uuid_from_string(uuid_str));
}
