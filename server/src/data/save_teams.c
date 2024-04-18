/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server_data.h"

json_object_t *serialize_team(roundtable_team_t *team)
{
    json_object_t *json = json_object_create(NULL);
    json_string_t *uuid = json_string_create("uuid",
        uuid_to_string(team->uuid));
    json_string_t *name = json_string_create("name", team->name);
    json_string_t *description = json_string_create("description",
        team->description);
    json_array_t *subscribers = serialize_subscribers(team);
    json_array_t *channels = serialize_channels(team);

    json_object_add(json, (json_t *) uuid);
    json_object_add(json, (json_t *) name);
    json_object_add(json, (json_t *) description);
    json_object_add(json, (json_t *) subscribers);
    json_object_add(json, (json_t *) channels);
    return json;
}

json_array_t *serialize_subscribers(roundtable_team_t *team)
{
    json_array_t *subscribers = json_array_create("subscribers");

    for (size_t i = 0; i < team->subscriber_count; i++) {
        json_array_add(subscribers,
            (json_t *) uuid_to_string(team->subscribers[i]));
    }
    return subscribers;
}

json_array_t *serialize_channels(roundtable_team_t *team)
{
    json_array_t *channels = json_array_create("channels");

    for (size_t i = 0; i < team->channel_count; i++) {
        json_array_add(channels,
            (json_t *) serialize_channel(&team->channels[i]));
    }
    return channels;
}
