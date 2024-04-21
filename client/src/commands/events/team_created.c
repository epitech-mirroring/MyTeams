/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** team_created
*/

#include "myclient.h"
#include "logging_client.h"

void team_created_callback(json_object_t *data, client_t *client)
{
    json_string_t *team_uuid =
        (json_string_t *)json_object_get(data, "team_uuid");
    json_string_t *team_name =
        (json_string_t *)json_object_get(data, "name");
    json_string_t *team_desc =
        (json_string_t *)json_object_get(data, "description");

    (void)client;
    if (team_uuid == NULL || team_name == NULL || team_desc == NULL)
        return;
    client_event_team_created(team_uuid->value, team_name->value,
        team_desc->value);
}
