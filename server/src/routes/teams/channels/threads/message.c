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

static response_t get_messages_list(roundtable_thread_t *thread)
{
    json_array_t *messages = json_array_create(NULL);
    json_object_t *message = NULL;

    for (size_t i = 0; i < thread->message_count; i++) {
        message = json_object_create(NULL);
        json_object_add(message, (json_t *) json_string_create("sender_uuid",
            uuid_to_string(thread->messages[i].sender_uuid)));
        json_object_add(message, (json_t *) json_string_create("content",
            thread->messages[i].content));
        json_object_add(message, (json_t *) json_number_create("timestamp",
            thread->messages[i].created_at));
        json_array_add(messages, (json_t *) message);
    }
    return create_success(200, json_serialize((json_t *) messages));
}

static bool has_mandatory_param(request_t *request)
{
    bool team_uuid = request_has_param(request, "team-uuid");
    bool channel_uuid = request_has_param(request, "channel-uuid");
    bool thread_uuid = request_has_param(request, "thread-uuid");

    return team_uuid && channel_uuid && thread_uuid;
}

static response_t validate_request_body(request_t *req,
    roundtable_server_t *srv)
{
    roundtable_client_instance_t *i = get_instance_from_header(srv, req);
    response_t rep = {0};
    roundtable_team_t *team = NULL;
    roundtable_channel_t *channel = NULL;
    roundtable_thread_t *thread = NULL;

    if (!i)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    team = get_team_from_param(req, srv, "team-uuid");
    if (!team)
        return create_error(404, "Team not found", "Team not found");
    channel = get_channel_from_param(team, req, srv, "channel-uuid");
    if (!channel)
        return create_error(404, "Channel not found", "Channel not found");
    if (!roundtable_team_has_subscriber(team, i->client))
        return create_error(403, "Forbidden", "Client not a subscriber");
    thread = get_thread_from_param(channel, req, srv, "thread-uuid");
    if (!thread)
        return create_error(404, "Thread not found", "Thread not found");
    return get_messages_list(thread);
}

response_t get_replies_route(request_t *req, void *data)
{
    roundtable_server_t *srv = (roundtable_server_t *)data;

    if (!IS_METHOD(req, "GET"))
        return create_error(405, "Method not allowed", "Only GET");
    if (!request_has_header(req, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    if (!has_mandatory_param(req))
        return create_error(400, "Invalid parameters",
            "Missing mandatory param");
    return validate_request_body(req, srv);
}
