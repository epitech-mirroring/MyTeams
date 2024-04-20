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

static uuid_t *get_thread_uuid(request_t *request)
{
    if (request_has_param(request, "thread-uuid"))
        return uuid_from_string(request_get_param(request, "thread-uuid"));
    return NULL;
}

static json_object_t *add_object_thread(roundtable_thread_t *thread)
{
    json_object_t *thread_json = json_object_create(NULL);

    json_object_add(thread_json, (json_t *)json_string_create("thread_uuid",
        uuid_to_string(thread->uuid)));
    json_object_add(thread_json, (json_t *)json_string_create("title",
        thread->title));
    json_object_add(thread_json, (json_t *)json_string_create("message",
        thread->content));
    json_object_add(thread_json, (json_t *)json_number_create("timestamp",
        thread->created_at));
    json_object_add(thread_json, (json_t *)json_string_create("sender_uuid",
        uuid_to_string(thread->sender_uuid)));
    return thread_json;
}

static response_t get_thread_list(roundtable_channel_t *channel,
    uuid_t *thread_in_param, response_t rep)
{
    json_array_t *response_body_array = json_array_create(NULL);
    json_object_t *threads = NULL;
    roundtable_thread_t *thread = NULL;

    if (!thread_in_param) {
        for (size_t i = 0; i < channel->thread_count; i++) {
            thread = &channel->threads[i];
            threads = add_object_thread(thread);
            json_array_add(response_body_array, (json_t *)threads);
        }
    } else {
        thread = roundtable_thread_find_by_uuid(channel, *thread_in_param);
        if (thread == NULL)
            return create_error(404, "Thread not found", "Thread not found");
        threads = add_object_thread(thread);
        json_array_add(response_body_array, (json_t *)threads);
    }
    rep = create_success(200, json_serialize((json_t *)response_body_array));
    return rep;
}

static bool has_mandatory_param(request_t *request)
{
    bool team_uuid = request_has_param(request, "team-uuid");
    bool channel_uuid = request_has_param(request, "channel-uuid");

    return team_uuid && channel_uuid;
}

static char *get_missing_key(request_t *request)
{
    if (!request_has_param(request, "channel-uuid"))
        return "Missing 'channel-uuid'";
    if (!request_has_param(request, "team-uuid"))
        return "Missing 'team-uuid'";
    return NULL;
}

static response_t validate_request_body(request_t *req,
    roundtable_server_t *srv, roundtable_team_t *team,
    roundtable_channel_t *channel)
{
    roundtable_client_t *client = get_client_from_header(srv, req);
    response_t rep = {0};

    if (!team)
        return create_error(404, "Team not found", "Team not found");
    if (!channel)
        return create_error(404, "Channel not found", "Channel not found");
    if (!client)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    if (!roundtable_team_has_subscriber(team, client))
        return create_error(403, "Forbidden", "Client not a subscriber");
    return get_thread_list(channel, get_thread_uuid(req), rep);
}

response_t get_threads_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *)data;
    roundtable_channel_t *channel = NULL;
    roundtable_team_t *team = NULL;

    if (!has_mandatory_param(request))
        return create_error(400, "Bad Request", get_missing_key(request));
    team = roundtable_server_get_team_by_uuid(server,
    *uuid_from_string(request_get_param(request, "team-uuid")));
    channel = roundtable_channel_find_by_uuid(team,
    *uuid_from_string(request_get_param(request, "channel-uuid")));
    if (request_has_param(request, "thread-uuid") && get_thread_from_string(
        channel, request_get_param(request, "thread-uuid")) == NULL)
        return create_error(404, "Thread not found", "Thread not found");
    return validate_request_body(request, server, team, channel);
}
