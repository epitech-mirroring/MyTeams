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
            status_to_string(user->status)));
        json_array_add(array, (json_t *) user_obj);
    }
    serialized = json_serialize((json_t *) array);
    json_destroy((json_t *) array);
    return serialized;
}

response_t team_users_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    roundtable_client_instance_t *instance = NULL;
    roundtable_team_t *team = NULL;

    if (!IS_METHOD(request, "GET"))
        return create_error(405, "Method not allowed", "Only GET");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    if (!request_has_param(request, "team-uuid"))
        return create_error(400, "Invalid params", "Missing 'team-uuid'");
    instance = get_instance_from_header(server, request);
    if (!instance)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    team = get_team_from_string(server,
        request_get_param(request, "team-uuid"));
    if (!team)
        return create_error(404, "Team not found", "Team not found");
    if (!roundtable_team_has_subscriber(team, instance->client))
        return create_error(403, "Forbidden", "Client not a subscriber");
    return create_success(200, serialize_users(server, team));
}
