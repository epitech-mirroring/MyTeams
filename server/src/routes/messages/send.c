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

static bool body_is_valid(json_object_t *body)
{
    bool receiver = json_object_has_key(body, "recipient_uuid");
    bool message = json_object_has_key(body, "message");

    return receiver && message;
}

static const char *get_missing_key(json_object_t *body)
{
    if (body == NULL)
        return "Missing 'recipient_uuid' and 'message'";
    if (!json_object_has_key(body, "recipient_uuid"))
        return "Missing 'recipient_uuid'";
    if (!json_object_has_key(body, "message"))
        return "Missing 'message'";
    return NULL;
}

static response_t server_event_success(roundtable_client_t *sender,
    roundtable_client_t *receiver, json_object_t *body)
{
    server_event_private_message_sended(uuid_to_string(sender->uuid),
    uuid_to_string(receiver->uuid),
    json_object_serialize((json_object_t *) json_object_get(body, "message")));
    return create_success(204, "");
}

response_t send_dm_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    json_object_t *body = (json_object_t *) json_parse(request->body);
    roundtable_client_instance_t *sender = NULL;
    roundtable_client_t *receiver = NULL;

    if (!IS_METHOD(request, "POST"))
        return create_error(405, "Method not allowed", "Only POST");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    if (!body || !body_is_valid(body))
        return create_error(400, "Invalid body", get_missing_key(body));
    sender = get_instance_from_header(server, request);
    if (!sender)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    receiver = get_client_from_json(server, body, "recipient_uuid");
    if (!receiver)
        return create_error(404, "Client not found", "Receiver not found");
    roundtable_server_send_dm(server, sender->client, receiver,
        ((json_object_t *) json_object_get(body, "message")));
    return server_event_success(sender->client, receiver, body);
}
