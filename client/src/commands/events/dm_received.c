/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** dm_received
*/

#include "myclient.h"
#include "logging_client.h"

void dm_received_callback(json_object_t *data, client_t *client)
{
    json_string_t *sender_uuid =
        (json_string_t *)json_object_get(data, "sender_uuid");
    json_object_t *message =
        (json_string_t *)json_object_get(data, "message");
    json_string_t *content = NULL;

    if (sender_uuid == NULL || message == NULL)
        return;
    content = (json_string_t *)json_object_get(message, "content");
    if (content == NULL)
        return;
    client_event_private_message_received(sender_uuid->value, content->value);
}
