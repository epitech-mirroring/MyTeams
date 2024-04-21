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
    char *client_uuid = uuid_to_string(client->uuid);
    char *team_uuid = uuid_to_string(team->uuid);

    server_event_user_unsubscribed(team_uuid, client_uuid);
    return create_success(204, "");
}

response_t leave_team_route(request_t *request, void *data)
{
    json_object_t *body = (json_object_t *) json_parse(request->body);
    roundtable_client_t *client = NULL;
    roundtable_team_t *team = NULL;

    if (!IS_METHOD(request, "POST"))
        return create_error(405, "Method not allowed", "Only POST");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    if (!body || !json_object_has_key(body, "team_uuid"))
        return create_error(400, "Invalid body", "Missing 'team_uuid'");
    client = get_client_from_header(data, request);
    if (!client)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    team = get_team_from_json(data, body, "team_uuid");
    if (!team)
        return create_error(404, "Team not found", "Team not found");
    if (!roundtable_team_has_subscriber(team, client))
        return create_error(409, "Not joined", "Client not a subscriber");
    roundtable_team_remove_subscriber(team, client);
    return server_event_success(client, team);
}
