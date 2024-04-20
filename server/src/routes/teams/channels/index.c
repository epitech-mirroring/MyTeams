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
#include "network/dto.h"

static uuid_t *get_channel_uuid_param(request_t *request)
{
    if (request_has_param(request, "channel-uuid")) {
        return uuid_from_string(request_get_param(request, "channel-uuid"));
    }
    return NULL;
}

static json_object_t *add_object_team(roundtable_channel_t *channel)
{
    json_object_t *channel_json = json_object_create(NULL);

    json_object_add(channel_json, (json_t *)json_string_create("uuid",
        uuid_to_string(channel->uuid)));
    json_object_add(channel_json, (json_t *)json_string_create("name",
        channel->name));
    json_object_add(channel_json, (json_t *)json_string_create("description",
        channel->description));
    return channel_json;
}

static response_t get_channels_list(roundtable_team_t *team,
    uuid_t *channel_in_param, response_t rep)
{
    json_array_t *response_body_array = json_array_create(NULL);
    json_object_t *channels = NULL;
    roundtable_channel_t *channel = NULL;

    if (!channel_in_param) {
        for (size_t i = 0; i < team->channel_count; i++) {
            channel = &team->channels[i];
            channels = add_object_team(channel);
            json_array_add(response_body_array, (json_t *)channels);
        }
    } else {
        channel = roundtable_channel_find_by_uuid(team, *channel_in_param);
        if (channel == NULL)
            return create_error(404, "Channel not found", "Channel not found");
        channels = add_object_team(channel);
        json_array_add(response_body_array, (json_t *)channels);
    }
    rep = create_success(200, json_serialize((json_t *)response_body_array));
    return rep;
}

response_t get_channels_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *)data;
    roundtable_client_t *client = NULL;
    uuid_t *channel_uuid = get_channel_uuid_param(request);
    roundtable_team_t *team = NULL;
    response_t rep = {0};

    if (!IS_METHOD(request, "GET"))
        return create_error(405, "Method disallowed", "Only GET Allowed");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization`");
    client = get_client_from_header(server, request);
    if (!client)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    if (!request_has_param(request, "team-uuid"))
        return create_error(403, "Forbidden", "Missing 'team-uuid'");
    if (!channel_uuid || request_has_param(request, "channel-uuid"))
        return create_error(404, "Channel not found", "Channel not found");
    team = roundtable_server_get_team_by_uuid(server,
    *uuid_from_string(request_get_param(request, "team-uuid")));
    return get_channels_list(team, channel_uuid, rep);
}
