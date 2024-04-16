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

void deserialize_message(json_object_t *message, roundtable_thread_t *thread)
{
    roundtable_message_t *new_message = calloc(1,
        sizeof(roundtable_message_t));
    json_string_t *sender_uuid = NULL;
    json_string_t *content = NULL;

    if (new_message == NULL)
        return;
    sender_uuid = (json_string_t *) json_object_get(message, "sender_uuid");
    content = (json_string_t *) json_object_get(message, "content");
    COPY_UUID(new_message->sender_uuid, sender_uuid->value);
    new_message->content = strdup(content->value);
    roundtable_thread_add_message(thread, new_message);
}

void deserialize_direct_messages(roundtable_server_t *server,
    json_array_t *direct_messages)
{
    for (size_t i = 0; i < direct_messages->size; i++) {
        deserialize_direct_message(server,
            (json_object_t *) json_array_get(direct_messages, i));
    }
}

void deserialize_direct_message(roundtable_server_t *server,
    json_object_t *message)
{
    roundtable_direct_message_t *new_message = calloc(1,
        sizeof(roundtable_direct_message_t));
    json_string_t *sender_uuid = NULL;
    json_string_t *rec_uuid = NULL;
    json_array_t *messages = NULL;

    if (new_message == NULL)
        return;
    sender_uuid = (json_string_t *) json_object_get(message, "sender_uuid");
    rec_uuid = (json_string_t *) json_object_get(message, "receiver_uuid");
    messages = (json_array_t *) json_object_get(message, "messages");
    COPY_UUID(new_message->sender_uuid, sender_uuid->value);
    COPY_UUID(new_message->receiver_uuid, rec_uuid->value);
    deserialize_direct_message_messages(messages, new_message);
    roundtable_server_add_direct_message(server, new_message);
}

void deserialize_direct_message_messages(json_array_t *messages,
    roundtable_direct_message_t *direct_message)
{
    for (size_t i = 0; i < messages->size; i++) {
        deserialize_direct_message_message(
            (json_object_t *) json_array_get(messages, i), direct_message);
    }
}

void deserialize_direct_message_message(json_object_t *message,
    roundtable_direct_message_t *direct_message)
{
    roundtable_message_t *new_message = calloc(1,
        sizeof(roundtable_message_t));
    json_string_t *sender_uuid = NULL;
    json_string_t *content = NULL;

    if (new_message == NULL)
        return;
    sender_uuid = (json_string_t *) json_object_get(message, "sender_uuid");
    content = (json_string_t *) json_object_get(message, "content");
    COPY_UUID(new_message->sender_uuid, sender_uuid->value);
    new_message->content = strdup(content->value);
    roundtable_direct_message_add_message(direct_message, new_message);
}
