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
    roundtable_server_add_team(server, new_team);
    return new_team;
}
