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
    channel->team = team;
    roundtable_team_add_channel(team, channel);
    return channel;
}

roundtable_channel_t *roundtable_channel_find_by_uuid(roundtable_team_t *team,
    uuid_t uuid)
{
    for (size_t i = 0; i < team->channel_count; i++) {
        if (uuid_compare(team->channels[i].uuid, uuid) == true)
            return &team->channels[i];
    }
    return NULL;
}

roundtable_channel_t *get_channel_from_json(roundtable_team_t *team,
    json_object_t *body, char *key)
{
    char *uuid_str = NULL;
    json_t *uuid_json = json_object_get(body, key);

    if (uuid_json == NULL || uuid_json->type != JSON_OBJECT_TYPE_STRING)
        return NULL;
    uuid_str = ((json_string_t *) uuid_json)->value;
    if (uuid_str == NULL || !uuid_from_string(uuid_str))
        return NULL;
    return roundtable_channel_find_by_uuid(team, *uuid_from_string(uuid_str));
}
