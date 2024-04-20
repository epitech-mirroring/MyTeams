/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** *
*/

#include "myclient.h"
#include "logging_client.h"

void thread_created_callback(json_object_t *data, client_t *client)
{
    json_string_t *thread_uuid =
        (json_string_t *)json_object_get(data, "thread_uuid");
    json_string_t *user_uuid =
        (json_string_t *)json_object_get(data, "sender_uuid");
    json_string_t *title =
        (json_string_t *)json_object_get(data, "title");
    json_string_t *content =
        (json_string_t *)json_object_get(data, "content");
    json_number_t *timestamp =
        (json_number_t *)json_object_get(data, "timestamp");

    if (thread_uuid == NULL || user_uuid == NULL || title == NULL ||
        content == NULL || timestamp == NULL)
        return;
    client_event_thread_created(thread_uuid->value, user_uuid->value,
        timestamp->value, title->value, content->value);
}
