/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server_data.h"

json_object_t *serialize_thread(roundtable_thread_t *thread)
{
    json_object_t *json = json_object_create(NULL);
    json_string_t *uuid = json_string_create("uuid",
        uuid_to_string(thread->uuid));
    json_string_t *title = json_string_create("title", thread->title);
    json_string_t *content = json_string_create("content", thread->content);
    json_array_t *replies = serialize_messages(thread->messages,
        thread->message_count);

    json_object_add(json, (json_t *) uuid);
    json_object_add(json, (json_t *) title);
    json_object_add(json, (json_t *) content);
    json_object_add(json, (json_t *) replies);
    return json;
}
