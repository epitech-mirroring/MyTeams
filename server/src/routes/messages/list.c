/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"
#include "server_utils.h"
#include "network/dto.h"

static response_t create_response(roundtable_direct_message_t **dm,
    roundtable_client_t *client)
{
    json_array_t *response = json_array_create(NULL);
    uuid_t *uuid = NULL;
    char *str = NULL;

    if (!dm || !client)
        return create_error(500, "Internal server error", !dm ? "No DMs" :
            "No client");
    for (size_t i = 0; dm[i]; i++) {
        if (uuid_compare(dm[i]->sender_uuid, client->uuid))
            uuid = &dm[i]->receiver_uuid;
        else
            uuid = &dm[i]->sender_uuid;
        json_array_add(response, (json_t *) json_string_create(
            NULL, uuid_to_string(*uuid)));
    }
    str = json_serialize((json_t *) response);
    json_array_destroy(response);
    free(dm);
    return create_success(200, str);
}

response_t list_direct_messages_route(request_t *request, void *data)
{
    roundtable_client_t *client = NULL;
    roundtable_direct_message_t **dm = NULL;

    if (!IS_METHOD(request, "GET"))
        return create_error(405, "Method not allowed", "Only GET");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    client = get_client_from_header(data, request);
    if (!client)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    dm = roundtable_server_get_messages_from_client(data, client);
    return create_response(dm, client);
}
