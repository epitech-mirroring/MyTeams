/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"
#include "json/json.h"
#include "server_utils.h"
#include "server_data.h"
#include "network/dto.h"

static char *serialize_dm_messages(roundtable_direct_message_t *dm)
{
    json_array_t *array = serialize_messages(dm->messages, dm->message_count);
    char *str = json_serialize((json_t *) array);

    json_array_destroy(array);
    return str;
}

response_t get_dms_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    json_object_t *body = (json_object_t *) json_parse(request->body);
    roundtable_client_t *sender = NULL;
    roundtable_client_t *receiver = NULL;
    roundtable_direct_message_t *dm = NULL;

    if (!IS_METHOD(request, "GET"))
        return create_error(405, "Method not allowed", "Only GET");
    if (!body || !json_object_has_key(body, "user_uuid"))
        return create_error(400, "Invalid body", "Missing 'user_uuid'");
    if (!request_has_param(request, "uuid"))
        return create_error(400, "Invalid request", "Missing 'uuid' param");
    sender = get_client_from_json(server, body, "user_uuid");
    if (!sender)
        return create_error(404, "Client not found", "Sender not found");
    receiver = roundtable_server_get_client_by_uuid(server, *uuid_from_string(
        request_get_param(request, "uuid")));
    if (!receiver)
        return create_error(404, "Client not found", "Receiver not found");
    dm = roundtable_server_find_direct_message(server, sender, receiver);
    if (!dm)
        return create_success(200, "[]");
    return create_success(200, serialize_dm_messages(dm));
}
