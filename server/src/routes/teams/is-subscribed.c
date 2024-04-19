/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"
#include "server_utils.h"
#include "network/dto.h"

response_t is_subscribed_route(request_t *request, void *data)
{
    roundtable_client_t *client = NULL;
    roundtable_team_t *team = NULL;

    if (!IS_METHOD(request, "GET"))
        return create_error(405, "Method not allowed", "Only GET");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    if (!request_has_param(request, "team-uuid"))
        return create_error(400, "Invalid param", "Missing 'team-uuid'");
    client = get_client_from_header(data, request);
    if (!client)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    team = get_team_from_string(data, request_get_param(request,
        "team-uuid"));
    if (!team)
        return create_error(404, "Team not found", "Team not found");
    if (!roundtable_team_has_subscriber(team, client))
        return create_success(200, "{\"subscribed\": false}");
    return create_success(200, "{\"subscribed\": true}");
}
