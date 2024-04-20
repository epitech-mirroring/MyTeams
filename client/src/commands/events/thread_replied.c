/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** thread_replied
*/

#include "myclient.h"
#include "logging_client.h"

void thread_replied_callback(json_object_t *data, client_t *client)
{
    json_string_t *team_uuid =
        (json_string_t *)json_object_get(data, "team_uuid");
    json_string_t *thread_uuid =
        (json_string_t *)json_object_get(data, "thread_uuid");
    json_string_t *replier_uuid =
        (json_string_t *)json_object_get(data, "sender_uuid");
    json_object_t *message = (json_object_t *)json_object_get(data, "message");
    json_string_t *content = NULL;

    if (team_uuid == NULL || thread_uuid == NULL || replier_uuid == NULL
        || message == NULL)
        return;
    content = (json_string_t *)json_object_get(message, "content");
    if (content == NULL)
        return;
    client_event_thread_reply_received(team_uuid->value, thread_uuid->value,
        replier_uuid->value, content->value);
}
