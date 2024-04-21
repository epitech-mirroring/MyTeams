/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"
#include "server_utils.h"
#include "network/dto.h"

static response_t server_event_success(roundtable_client_t *client,
    roundtable_team_t *team)
{
    char *team_uuid = uuid_to_string(team->uuid);
    char *client_uuid = uuid_to_string(client->uuid);

    server_event_user_subscribed(team_uuid, client_uuid);
    return create_success(204, "");
}

response_t join_team_route(request_t *request, void *data)
{
    json_object_t *body = (json_object_t *) json_parse(request->body);
    roundtable_client_instance_t *instance = NULL;
    roundtable_team_t *team = NULL;

    if (!IS_METHOD(request, "POST"))
        return create_error(405, "Method not allowed", "Only POST");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    if (!body || !json_object_has_key(body, "team_uuid"))
        return create_error(400, "Invalid body", "Missing 'team_uuid'");
    instance = get_instance_from_header(data, request);
    if (!instance)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    team = get_team_from_json(data, body, "team_uuid");
    if (!team)
        return create_error(404, "Team not found", "Team not found");
    if (roundtable_team_has_subscriber(team, instance->client))
        return create_error(409, "Already joined", "Client already joined");
    roundtable_team_add_subscriber(team, instance->client);
    return server_event_success(instance->client, team);
}
