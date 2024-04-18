/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"
#include "server_utils.h"

static bool body_is_valid(json_object_t *body)
{
    bool sender = json_object_has_key(body, "user_uuid");
    bool team = json_object_has_key(body, "team_uuid");

    return sender && team;
}

static const char *get_missing_key(json_object_t *body)
{
    if (body == NULL)
        return "Missing 'user_uuid' and 'team_uuid'";
    if (!json_object_has_key(body, "user_uuid"))
        return "Missing 'user_uuid'";
    if (!json_object_has_key(body, "team_uuid"))
        return "Missing 'team_uuid'";
    return NULL;
}

static char *serialize_users(roundtable_server_t *server,
    roundtable_team_t *team)
{
    char *serialized = NULL;
    json_object_t *user_obj = NULL;
    roundtable_client_t *user = NULL;
    json_array_t *array = json_array_create(NULL);

    for (size_t i = 0; i < team->subscriber_count; i++) {
        user = roundtable_server_get_client_by_uuid(server,
            team->subscribers[i]);
        user_obj = json_object_create(NULL);
        json_object_add(user_obj, (json_t *) json_string_create("uuid",
            uuid_to_string(user->uuid)));
        json_object_add(user_obj, (json_t *) json_string_create("username",
            user->username));
        json_object_add(user_obj, (json_t *) json_string_create("status",
            user->status == ONLINE ? "ONLINE" : "OFFLINE"));
        json_array_add(array, (json_t *) user_obj);
    }
    serialized = json_serialize((json_t *) array);
    json_destroy((json_t *) array);
    return serialized;
}

response_t team_users_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    json_object_t *body = (json_object_t *) json_parse(request->body);
    roundtable_client_t *client = NULL;
    roundtable_team_t *team = NULL;

    if (!IS_METHOD(request, "GET"))
        return create_error(405, "Method not allowed", "Only GET");
    if (!body || !body_is_valid(body))
        return create_error(400, "Invalid body", get_missing_key(body));
    client = get_client_from_json(server, body, "user_uuid");
    if (!client)
        return create_error(404, "Client not found", "Client not found");
    team = get_team_from_json(server, body, "team_uuid");
    if (!team)
        return create_error(404, "Team not found", "Team not found");
    if (!roundtable_team_has_subscriber(team, client))
        return create_error(403, "Forbidden", "Client not a subscriber");
    return create_success(200, serialize_users(server, team));
}
