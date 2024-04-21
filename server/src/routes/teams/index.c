/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdbool.h>
#include "server.h"
#include "server_utils.h"
#include "network/dto.h"

static json_object_t *dto_team(roundtable_team_t *team)
{
    json_object_t *team_json = json_object_create(NULL);

    json_object_add(team_json, (json_t *) json_string_create("team_uuid",
        uuid_to_string(team->uuid)));
    json_object_add(team_json, (json_t *) json_string_create("team_name",
        team->name));
    json_object_add(team_json, (json_t *) json_string_create(
        "team_description", team->description));
    return team_json;
}

static void dto_teams(const roundtable_server_t *server,
    roundtable_client_t *client, bool only_joined,
    json_array_t *res_body)
{
    roundtable_team_t *team = NULL;

    for (size_t i = 0; i < server->team_count; i++) {
        team = server->teams[i];
        if (only_joined && !roundtable_team_has_subscriber(team, client))
            continue;
        json_array_add(res_body, (json_t *) dto_team(team));
    }
}

static response_t handle_get_teams(roundtable_server_t *server,
    roundtable_client_t *client, uuid_t *team_uuid, bool only_joined)
{
    json_array_t *res_body = json_array_create(NULL);
    roundtable_team_t *team = NULL;
    response_t response;

    if (team_uuid) {
        team = roundtable_server_get_team_by_uuid(server, *team_uuid);
        if (team == NULL)
            return create_error(404, "Team not found", "Team not found");
        json_array_add(res_body, (json_t *) dto_team(team));
    } else {
        dto_teams(server, client, only_joined, res_body);
    }
    response = create_success(200, json_serialize((json_t *) res_body));
    json_destroy((json_t *) res_body);
    return response;
}

response_t get_teams_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    roundtable_client_instance_t *instance = NULL;
    uuid_t *team_uuid = NULL;
    bool only_joined = false;

    if (!IS_METHOD(request, "GET") != 0)
        return create_error(405, "Method not allowed", "Only GET");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    instance = get_instance_from_header(server, request);
    if (!instance)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    if (request_has_param(request, "team-uuid"))
        team_uuid = uuid_from_string(request_get_param(request, "team-uuid"));
    if (!team_uuid && request_has_param(request, "team-uuid"))
        return create_error(404, "Team not found", "Team not found");
    if (request_has_param(request, "only-joined"))
        only_joined = strcmp(request_get_param(request, "only-joined"),
            "true") == 0;
    return handle_get_teams(server, instance->client, team_uuid, only_joined);
}
