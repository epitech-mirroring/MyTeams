/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"
#include "server_utils.h"

static bool body_is_valid(json_object_t *body)
{
    bool sender = json_object_has_key(body, "user_uuid");
    bool team = json_object_has_key(body, "team_uuid");
    bool name = json_object_has_key(body, "name");
    bool description = json_object_has_key(body, "description");

    return sender && name && description && team;
}

static const char *get_missing_key(json_object_t *body)
{
    if (body == NULL)
        return "Missing 'user_uuid', 'team_uuid', 'name' and 'description'";
    if (!json_object_has_key(body, "user_uuid"))
        return "Missing 'user_uuid'";
    if (!json_object_has_key(body, "team_uuid"))
        return "Missing 'team_uuid'";
    if (!json_object_has_key(body, "name"))
        return "Missing 'name'";
    if (!json_object_has_key(body, "description"))
        return "Missing 'description'";
    return NULL;
}

static response_t create_channel_response_body(roundtable_channel_t *channel)
{
    json_object_t *body = json_object_create(NULL);
    char *body_str = NULL;
    response_t response;

    json_object_add(body, (json_t *) json_string_create("channel_uuid",
        uuid_to_string(channel->uuid)));
    body_str = json_serialize((json_t *) body);
    json_object_destroy(body);
    response = create_success(201, body_str);
    free(body_str);
    return response;
}

static response_t create_channel_response(roundtable_server_t *server,
    roundtable_team_t *team, json_object_t *body)
{
    roundtable_channel_t *channel = roundtable_channel_create(
        ((json_string_t *) json_object_get(body, "name"))->value,
        ((json_string_t *) json_object_get(body, "description"))->value,
        team);

    return create_channel_response_body(channel);
}

response_t create_channel_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    json_object_t *body = (json_object_t *) json_parse(request->body);
    roundtable_client_t *client = NULL;
    roundtable_team_t *team = NULL;

    if (strcmp(request->route.method, "POST") != 0)
        return create_error(405, "Method not allowed", "Only POST");
    if (body == NULL || !body_is_valid(body))
        return create_error(400, "Invalid body", get_missing_key(body));
    client = get_client_from_json(server, body, "user_uuid");
    if (!client)
        return create_error(404, "Client not found", "Client not found");
    team = get_team_from_json(server, body, "team_uuid");
    if (!team)
        return create_error(404, "Team not found", "Team not found");
    if (!roundtable_team_has_subscriber(team, client))
        return create_error(403, "Forbidden", "Client not a subscriber");
    return create_channel_response(server, team, body);
}
