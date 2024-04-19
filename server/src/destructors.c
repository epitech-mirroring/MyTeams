/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

static void destroy_channels(roundtable_channel_t *channels, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        destroy_channel(channels[i]);
    }
    free(channels);
}

static void destroy_threads(roundtable_thread_t *threads, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        destroy_thread(threads[i]);
    }
    free(threads);
}

void destroy_client(roundtable_client_t *client)
{
    free(client->username);
    free(client);
}

void destroy_team(roundtable_team_t *team)
{
    free(team->name);
    free(team->description);
    destroy_channels(team->channels, team->channel_count);
    free(team->subscribers);
    free(team);
}

void destroy_message(roundtable_message_t message)
{
    free(message.content);
}

void destroy_channel(roundtable_channel_t channel)
{
    free(channel.name);
    free(channel.description);
    destroy_threads(channel.threads, channel.thread_count);
}
