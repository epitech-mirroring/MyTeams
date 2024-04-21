/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

static void send_channel_created_event(roundtable_server_t *server,
    roundtable_client_instance_t **instances, roundtable_channel_t *channel)
{
    json_object_t *data = NULL;

    for (size_t i = 0; instances[i]; i++) {
        data = json_object_create(NULL);
        json_object_add(data, (json_t *) json_string_create("team_uuid",
            uuid_to_string(channel->team->uuid)));
        json_object_add(data, (json_t *) json_string_create("channel_uuid",
            uuid_to_string(channel->uuid)));
        json_object_add(data, (json_t *) json_string_create("name",
            channel->name));
        json_object_add(data, (json_t *) json_string_create("description",
            channel->description));
        roundtable_server_send_event(server, instances[i],
            roundtable_server_create_event(CHANNEL_CREATED, data));
    }
    free(instances);
}

void roundtable_event_channel_created(roundtable_server_t *server,
    roundtable_channel_t *channel)
{
    roundtable_client_t *client = NULL;
    roundtable_client_instance_t **instances = NULL;

    for (size_t i = 0; i < channel->team->subscriber_count; i++) {
        client = roundtable_server_get_client_by_uuid(server,
            channel->team->subscribers[i]);
        instances = roundtable_client_instances_find(server, client);
        send_channel_created_event(server, instances, channel);
    }
}
