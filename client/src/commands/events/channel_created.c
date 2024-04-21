/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** channel_created
*/

#include "myclient.h"
#include "logging_client.h"

void channel_created_callback(json_object_t *data, client_t *client)
{
    json_string_t *channel_uuid =
        (json_string_t *)json_object_get(data, "channel_uuid");
    json_string_t *channel_name =
        (json_string_t *)json_object_get(data, "name");
    json_string_t *channel_desc =
        (json_string_t *)json_object_get(data, "description");

    (void)client;
    if (channel_uuid == NULL || channel_name == NULL || channel_desc == NULL)
        return;
    client_event_channel_created(channel_uuid->value, channel_name->value,
        channel_desc->value);
}
