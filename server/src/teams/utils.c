/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

void roundtable_server_add_team(roundtable_server_t *server,
    roundtable_team_t *team)
{
    roundtable_team_t **new_teams = NULL;

    new_teams = realloc(server->teams,
        sizeof(roundtable_team_t *) * (server->team_count + 1));
    if (new_teams == NULL)
        return;
    server->teams = new_teams;
    server->teams[server->team_count] = team;
    server->team_count++;
}

void roundtable_team_add_channel(roundtable_team_t *team,
    roundtable_channel_t *channel)
{
    roundtable_channel_t *new_channels = NULL;

    new_channels = realloc(team->channels,
        sizeof(roundtable_channel_t) * (team->channel_count + 1));
    if (new_channels == NULL)
        return;
    team->channels = new_channels;
    team->channels[team->channel_count] = *channel;
    team->channel_count++;
}

void roundtable_team_add_subscriber(roundtable_team_t *team,
    roundtable_client_t *subscriber)
{
    uuid_t *new_subscribers = NULL;

    new_subscribers = realloc(team->subscribers,
        sizeof(uuid_t) * (team->subscriber_count + 1));
    if (new_subscribers == NULL)
        return;
    team->subscribers = new_subscribers;
    COPY_UUID(team->subscribers[team->subscriber_count], subscriber->uuid);
    team->subscriber_count++;
}

static size_t get_subscriber_index(roundtable_team_t *team,
    roundtable_client_t *subscriber, bool *found)
{
    for (size_t i = 0; i < team->subscriber_count; i++) {
        if (uuid_compare(team->subscribers[i], subscriber->uuid)) {
            *found = true;
            return i;
        }
    }
    *found = false;
    return 0;
}

void roundtable_team_remove_subscriber(roundtable_team_t *team,
    roundtable_client_t *subscriber)
{
    size_t index;
    bool found = false;
    uuid_t *subscribers = NULL;

    index = get_subscriber_index(team, subscriber, &found);
    if (!found)
        return;
    subscribers = calloc(team->subscriber_count - 1, sizeof(uuid_t));
    if (subscribers == NULL)
        return;
    for (size_t i = 0; i < team->subscriber_count; i++) {
        if (i == index)
            continue;
        COPY_UUID(subscribers[i], team->subscribers[i]);
    }
    free(team->subscribers);
    team->subscribers = subscribers;
    team->subscriber_count--;
}
