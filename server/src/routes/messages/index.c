/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"
#include "server_utils.h"
#include "server_data.h"
#include "network/dto.h"

static char *serialize(roundtable_direct_message_t *dm)
{
    json_array_t *array = NULL;
    char *str = NULL;

    if (!dm)
        return "[]";
    array = serialize_messages(dm->messages, dm->message_count);
    str = json_serialize((json_t *) array);
    json_array_destroy(array);
    return str;
}

response_t get_dms_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    roundtable_client_t *s = NULL;
    roundtable_client_t *r = NULL;

    if (!IS_METHOD(request, "GET"))
        return create_error(405, "Method not allowed", "Only GET");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    if (!request_has_param(request, "uuid"))
        return create_error(400, "Invalid request", "Missing 'uuid' param");
    s = get_client_from_header(server, request);
    if (!s)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    r = roundtable_server_get_client_by_uuid(server, *uuid_from_string(
        request_get_param(request, "uuid")));
    if (!r)
        return create_error(404, "Client not found", "Receiver not found");
    return create_success(200,
        serialize(roundtable_server_find_direct_message(server, s, r)));
}
