/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "uuid/uuid.h"
#include "server.h"

void roundtable_server_send_dm(roundtable_server_t *server,
    roundtable_client_t *s, roundtable_client_t *r,
    json_object_t *message)
{
    roundtable_direct_message_t *direct_message = NULL;
    roundtable_message_t *new_message = NULL;

    direct_message = roundtable_server_find_direct_message(server, s, r);
    if (direct_message == NULL) {
        direct_message = roundtable_direct_message_create(s, r);
        if (direct_message == NULL)
            return;
        roundtable_server_add_direct_message(server, direct_message);
    }
    new_message = roundtable_message_create(s, message);
    if (new_message == NULL)
        return;
    roundtable_direct_message_add_message(direct_message, new_message);
}

roundtable_direct_message_t *roundtable_server_find_direct_message(
    roundtable_server_t *server, roundtable_client_t *s,
    roundtable_client_t *r)
{
    roundtable_direct_message_t *a = NULL;
    roundtable_direct_message_t *b = NULL;

    for (size_t i = 0; i < server->message_count; i++) {
        if (uuid_compare(server->direct_messages[i]->sender_uuid, s->uuid)
        && uuid_compare(server->direct_messages[i]->receiver_uuid, r->uuid))
            a = server->direct_messages[i];
        if (uuid_compare(server->direct_messages[i]->sender_uuid, r->uuid)
        && uuid_compare(server->direct_messages[i]->receiver_uuid, s->uuid))
            b = server->direct_messages[i];
    }
    if (a != NULL)
        return a;
    return b;
}

roundtable_direct_message_t *roundtable_direct_message_create(
    roundtable_client_t *s, roundtable_client_t *r)
{
    roundtable_direct_message_t *new_direct_message =
        calloc(1, sizeof(roundtable_direct_message_t));

    if (new_direct_message == NULL)
        return NULL;
    uuid_copy(new_direct_message->sender_uuid, s->uuid);
    uuid_copy(new_direct_message->receiver_uuid, r->uuid);
    new_direct_message->message_count = 0;
    new_direct_message->messages = NULL;
    return new_direct_message;
}

roundtable_message_t *roundtable_message_create(roundtable_client_t *s,
    json_object_t *message)
{
    roundtable_message_t *new_message = calloc(1,
        sizeof(roundtable_message_t));

    if (new_message == NULL)
        return NULL;
    if (!json_object_has_key(message, "content")) {
        free(new_message);
        return NULL;
    }
    COPY_UUID(new_message->sender_uuid, s->uuid);
    new_message->content = strdup(((json_string_t *)
        json_object_get(message, "content"))->value);
    return new_message;
}
