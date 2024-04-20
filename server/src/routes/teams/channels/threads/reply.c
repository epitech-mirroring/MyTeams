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
    bool message_content = NULL;
    bool team = json_object_has_key(body, "team_uuid");
    bool name = json_object_has_key(body, "channel_uuid");
    bool description = json_object_has_key(body, "thread_uuid");
    bool message = json_object_has_key(body, "message");

    if (message){
        message_content = json_object_has_key(((json_object_t *)
            json_object_get(body, "message")), "content");
    }
    return name && description && team && message && message_content;
}

static const char *get_missing_key(json_object_t *body)
{
    if (body == NULL)
        return "Missing 'team_uuid', 'channel_uuid', 'thread_uuid', 'message'";
    if (!json_object_has_key(body, "team_uuid"))
        return "Missing 'team_uuid'";
    if (!json_object_has_key(body, "channel_uuid"))
        return "Missing 'channel_uuid'";
    if (!json_object_has_key(body, "thread_uuid"))
        return "Missing 'thread_uuid'";
    if (!json_object_has_key(body, "message"))
        return "Missing 'message'";
    if (!json_object_has_key(((json_object_t *)json_object_get(body,
        "message")), "content"))
        return "Missing 'message content'";
    return NULL;
}

static response_t create_reply_response_body(roundtable_thread_t *thread,
    json_object_t *body, roundtable_client_t *sender)
{
    json_object_t *message = (json_object_t *)json_object_get(body, "message");
    roundtable_message_t *reply = roundtable_reply_create(
        ((json_string_t *)json_object_get(message, "content"))->value,
        sender, thread);
    json_object_t *response_body = json_object_create(NULL);
    char *response_body_str = NULL;
    response_t response;

    json_object_add(response_body, (json_t *) json_number_create("timestamp",
    reply->created_at));
    response_body_str = json_serialize((json_t *) response_body);
    json_object_destroy(response_body);
    response = create_success(201, response_body_str);
    free(response_body_str);
    return response;
}

static response_t validate_request(roundtable_server_t *server,
    roundtable_client_t *client, json_object_t *body)
{
    roundtable_team_t *team = NULL;
    roundtable_channel_t *channel = NULL;
    roundtable_thread_t *thread = NULL;

    team = get_team_from_json(server, body, "team_uuid");
    if (team == NULL)
        return create_error(404, "Team not found", "Team not found");
    if (!roundtable_team_has_subscriber(team, client))
        return create_error(403, "Forbidden", "Client not in team");
    channel = get_channel_from_json(team, body, "channel_uuid");
    if (channel == NULL)
        return create_error(404, "Channel not found", "Channel not found");
    thread = get_thread_from_json(channel, body, "thread_uuid");
    if (thread == NULL)
        return create_error(404, "Thread not found", "Thread not found");
    return create_reply_response_body(thread, body, client);
}

response_t create_reply_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    json_object_t *body = (json_object_t *) json_parse(request->body);
    roundtable_client_t *client = get_client_from_header(server, request);

    if (strcmp(request->route.method, "POST") != 0)
        return create_error(405, "Method not allowed", "Only POST");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    if (body == NULL || !body_is_valid(body))
        return create_error(400, "Invalid body", get_missing_key(body));
    return validate_request(server, client, body);
}
