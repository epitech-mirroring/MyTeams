/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"
#include "server_data.h"

void roundtable_event_dm_received(roundtable_server_t *server,
    roundtable_message_t *msg, roundtable_client_t *receiver,
    roundtable_client_t *sender)
{
    json_object_t *data = NULL;
    json_object_t *message = serialize_message(msg);
    roundtable_client_instance_t **instances =
        roundtable_client_instances_find(server, receiver);

    while (*instances) {
        data = json_object_create(NULL);
        json_object_add(data, (json_t *) json_string_create("sender_uuid",
            uuid_to_string(sender->uuid)));
        free(message->base.key);
        message->base.key = strdup("message");
        json_object_add(data, (json_t *) message);
        roundtable_server_send_event(server, *instances,
            roundtable_server_create_event(DM_RECEIVED, data));
        instances++;
    }
    free(instances);
}
