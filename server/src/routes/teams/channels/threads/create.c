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

static bool body_is_valid(json_object_t *body)
{
    bool team = json_object_has_key(body, "team_uuid");
    bool name = json_object_has_key(body, "channel_uuid");
    bool description = json_object_has_key(body, "title");
    bool message = json_object_has_key(body, "message");

    return name && description && team && message;
}

static const char *get_missing_key(json_object_t *body)
{
    if (body == NULL)
        return "Missing 'team_uuid', 'channel_uuid', 'title' and 'message'";
    if (!json_object_has_key(body, "team_uuid"))
        return "Missing 'team_uuid'";
    if (!json_object_has_key(body, "channel_uuid"))
        return "Missing 'channel_uuid'";
    if (!json_object_has_key(body, "title"))
        return "Missing 'title'";
    if (!json_object_has_key(body, "message"))
        return "Missing 'message'";
    return NULL;
}

static response_t create_thread_response_body(roundtable_thread_t *thread)
{
    json_object_t *body = json_object_create(NULL);
    char *body_str = NULL;
    response_t response;

    json_object_add(body, (json_t *) json_string_create("thread_uuid",
    uuid_to_string(thread->uuid)));
    json_object_add(body, (json_t *) json_number_create("timestamp",
    thread->created_at));
    body_str = json_serialize((json_t *) body);
    json_object_destroy(body);
    response = create_success(201, body_str);
    free(body_str);
    roundtable_event_thread_created(thread->channel->team->server, thread);
    return response;
}

static response_t create_thread_response(roundtable_channel_t *channel,
    json_object_t *body, roundtable_client_t *client)
{
    roundtable_thread_t *thread = roundtable_thread_create(
        ((json_string_t *) json_object_get(body, "title"))->value,
        ((json_string_t *) json_object_get(body, "message"))->value,
        channel, client);

    return create_thread_response_body(thread);
}

static response_t validate_request(request_t *req, roundtable_server_t *srv,
    roundtable_client_t *client, json_object_t *body)
{
    roundtable_team_t *team = get_team_from_json(srv, body, "team_uuid");
    roundtable_channel_t *channel = NULL;

    if (!request_has_header(req, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    if (!client)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    if (!team)
        return create_error(404, "Team not found", "Team not found");
    if (!roundtable_team_has_subscriber(team, client))
        return create_error(403, "Forbidden", "Client not a subscriber");
    channel = get_channel_from_json(team, body,
    "channel_uuid");
    if (!channel)
        return create_error(404, "Channel not found", "Channel not found");
    return create_thread_response(channel, body, client);
}

response_t create_thread_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    json_object_t *body = (json_object_t *) json_parse(request->body);
    roundtable_client_t *client = get_client_from_header(server, request);

    if (strcmp(request->route.method, "POST") != 0)
        return create_error(405, "Method not allowed", "Only POST");
    if (!body || !body_is_valid(body))
        return create_error(400, "Invalid body", get_missing_key(body));
    return validate_request(request, server, client, body);
}
