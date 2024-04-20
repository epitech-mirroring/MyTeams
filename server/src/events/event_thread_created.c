/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"

void roundtable_event_thread_created(roundtable_server_t *server,
    roundtable_thread_t *thread)
{
    json_object_t *data = NULL;
    roundtable_client_t *client = NULL;

    for (size_t i = 0; i < thread->channel->team->subscriber_count; i++) {
        client = roundtable_server_get_client_by_uuid(server,
            thread->channel->team->subscribers[i]);
        data = json_object_create(NULL);
        json_object_add(data, (json_t *) json_string_create("team_uuid",
            uuid_to_string(thread->channel->team->uuid)));
        json_object_add(data, (json_t *) json_string_create("channel_uuid",
            uuid_to_string(thread->channel->uuid)));
        json_object_add(data, (json_t *) json_string_create("thread_uuid",
            uuid_to_string(thread->uuid)));
        json_object_add(data, (json_t *) json_string_create("sender_uuid",
            uuid_to_string(thread->sender_uuid)));
        json_object_add(data, (json_t *) json_string_create("title",
            thread->title));
        json_object_add(data, (json_t *) json_string_create("content",
            thread->content));
        json_object_add(data, (json_t *) json_number_create("timestamp",
            thread->created_at));
        roundtable_server_send_event(server, client,
            roundtable_server_create_event(THREAD_CREATED, data));
    }
}
