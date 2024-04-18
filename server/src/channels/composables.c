/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

roundtable_channel_t *roundtable_channel_create(const char *name,
    const char *description, roundtable_team_t *team)
{
    roundtable_channel_t *channel = malloc(sizeof(roundtable_channel_t));

    if (channel == NULL)
        return NULL;
    COPY_UUID(channel->uuid, *uuid_generate());
    channel->name = strdup(name);
    channel->description = strdup(description);
    channel->thread_count = 0;
    channel->threads = NULL;
    roundtable_team_add_channel(team, channel);
    return channel;
}
