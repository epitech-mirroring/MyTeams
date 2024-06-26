/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

roundtable_team_t *roundtable_server_get_team_by_uuid(
    roundtable_server_t *server, uuid_t uuid)
{
    for (size_t i = 0; i < server->team_count; i++) {
        if (uuid_compare(server->teams[i]->uuid, uuid))
            return server->teams[i];
    }
    return NULL;
}

roundtable_team_t *roundtable_server_create_team(
    roundtable_server_t *server, const char *name, const char *description)
{
    roundtable_team_t *new_team = calloc(1, sizeof(roundtable_team_t));

    if (new_team == NULL)
        return NULL;
    uuid_copy(new_team->uuid, *uuid_generate());
    new_team->name = strdup(name);
    new_team->description = strdup(description);
    new_team->channels = NULL;
    new_team->subscribers = NULL;
    new_team->channel_count = 0;
    new_team->subscriber_count = 0;
    new_team->server = server;
    roundtable_server_add_team(server, new_team);
    return new_team;
}

bool roundtable_team_has_subscriber(
    roundtable_team_t *team, roundtable_client_t *client)
{
    for (size_t i = 0; i < team->subscriber_count; i++) {
        if (uuid_compare(team->subscribers[i], client->uuid))
            return true;
    }
    return false;
}

roundtable_team_t *get_team_from_json(
    roundtable_server_t *server, json_object_t *body, char *key)
{
    char *uuid_str = NULL;
    json_t *uuid_json = json_object_get(body, key);

    if (uuid_json == NULL || uuid_json->type != JSON_OBJECT_TYPE_STRING)
        return NULL;
    uuid_str = ((json_string_t *) uuid_json)->value;
    if (uuid_str == NULL || !uuid_from_string(uuid_str))
        return NULL;
    return roundtable_server_get_team_by_uuid(server,
        *uuid_from_string(uuid_str));
}

roundtable_team_t *get_team_from_string(
    roundtable_server_t *server, char *uuid_str)
{
    if (uuid_str == NULL || strlen(uuid_str) != 32)
        return NULL;
    return roundtable_server_get_team_by_uuid(server,
        *uuid_from_string(uuid_str));
}
