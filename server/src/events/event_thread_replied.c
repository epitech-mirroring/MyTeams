/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"
#include "server_data.h"

static json_object_t *s_message(roundtable_message_t *message)
{
    json_object_t *json = json_object_create("message");
    json_string_t *content = json_string_create("content", message->content);

    json_object_add(json, (json_t *) content);
    return json;
}

void roundtable_event_thread_reply(roundtable_server_t *server,
    roundtable_thread_t *thread)
{
    json_object_t *data = NULL;
    roundtable_client_t *client = NULL;
    roundtable_message_t msg = thread->messages[thread->message_count - 1];

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
            uuid_to_string(msg.sender_uuid)));
        json_object_add(data, (json_t *) s_message(&msg));
        roundtable_server_send_event(server, client,
            roundtable_server_create_event(THREAD_REPLIED, data));
    }
}
