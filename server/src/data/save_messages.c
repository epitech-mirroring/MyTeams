/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server_data.h"

json_array_t *serialize_messages(roundtable_message_t *messages,
    size_t message_count)
{
    json_array_t *json = json_array_create("messages");

    for (size_t i = 0; i < message_count; i++) {
        json_array_add(json, (json_t *) serialize_message(&messages[i]));
    }
    return json;
}

json_object_t *serialize_message(roundtable_message_t *message)
{
    json_object_t *json = json_object_create(NULL);
    json_string_t *content = json_string_create("content", message->content);
    json_string_t *sender = json_string_create("sender_uuid",
        uuid_to_string(message->sender_uuid));

    json_object_add(json, (json_t *) content);
    json_object_add(json, (json_t *) sender);
    return json;
}

json_object_t *serialize_direct_message(roundtable_direct_message_t *message)
{
    json_object_t *json = json_object_create(NULL);
    json_string_t *sender = json_string_create("sender_uuid",
        uuid_to_string(message->sender_uuid));
    json_string_t *receiver = json_string_create("receiver_uuid",
        uuid_to_string(message->receiver_uuid));
    json_array_t *messages = serialize_messages(message->messages,
        message->message_count);

    json_object_add(json, (json_t *) messages);
    json_object_add(json, (json_t *) sender);
    json_object_add(json, (json_t *) receiver);
    return json;
}
