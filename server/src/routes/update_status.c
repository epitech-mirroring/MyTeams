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

response_t update_status_route(request_t *request, void *data)
{
    json_object_t *body = (json_object_t *) json_parse(request->body);
    roundtable_client_instance_t *instance = NULL;

    if (!IS_METHOD(request, "POST"))
        return create_error(405, "Method not allowed", "Only POST");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    if (!body || !json_object_has_key(body, "status"))
        return create_error(400, "Invalid body", "Missing 'status'");
    instance = get_instance_from_header(data, request);
    if (!instance)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    instance->client->status = status_from_string(
        ((json_string_t *) json_object_get(body, "status"))->value);
    return create_success(204, "");
}
