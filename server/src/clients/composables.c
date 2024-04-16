/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"

roundtable_client_t *roundtable_server_get_client_by_uuid(
    roundtable_server_t *server, uuid_t uuid)
{
    for (size_t i = 0; i < server->client_count; i++) {
        if (uuid_compare(server->clients[i].uuid, uuid) == 0)
            return &server->clients[i];
    }
    return NULL;
}
