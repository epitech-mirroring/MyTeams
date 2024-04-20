/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"
#include "network/dto.h"

void roundtable_thread_add_message(roundtable_thread_t *thread,
    roundtable_message_t *message)
{
    roundtable_message_t *new_messages = NULL;

    new_messages = realloc(thread->messages,
        sizeof(roundtable_message_t) * (thread->message_count + 1));
    if (new_messages == NULL)
        return;
    thread->messages = new_messages;
    thread->messages[thread->message_count] = *message;
    thread->message_count++;
}

roundtable_thread_t *get_thread_from_param(roundtable_channel_t *channel,
    request_t *request, roundtable_server_t *server, char *key)
{
    uuid_t *thread_uuid = uuid_from_string(request_get_param(request, key));
    roundtable_thread_t *thread = NULL;

    if (thread_uuid == NULL)
        return NULL;
    for (size_t i = 0; i < channel->thread_count; i++) {
        if (uuid_compare(channel->threads[i].uuid, *thread_uuid)) {
            thread = &channel->threads[i];
            break;
        }
    }
    return thread;
}

roundtable_channel_t *get_channel_from_param(roundtable_team_t *team,
    request_t *request, roundtable_server_t *server, char *key)
{
    uuid_t *channel_uuid = uuid_from_string(request_get_param(request, key));
    roundtable_channel_t *channel = NULL;

    if (channel_uuid == NULL)
        return NULL;
    for (size_t i = 0; i < team->channel_count; i++) {
        if (uuid_compare(team->channels[i].uuid, *channel_uuid)) {
            channel = &team->channels[i];
            break;
        }
    }
    return channel;
}

roundtable_team_t *get_team_from_param(request_t *request,
    roundtable_server_t *server, char *key)
{
    uuid_t *team_uuid = uuid_from_string(request_get_param(request, key));
    roundtable_team_t *team = NULL;

    if (team_uuid == NULL)
        return NULL;
    for (size_t i = 0; i < server->team_count; i++) {
        if (uuid_compare(server->teams[i]->uuid, *team_uuid)) {
            team = server->teams[i];
            break;
        }
    }
    return team;
}
