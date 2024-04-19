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
#include "network/dto.h"

roundtable_client_t *roundtable_server_get_client_by_uuid(
    roundtable_server_t *server, uuid_t uuid)
{
    for (size_t i = 0; i < server->client_count; i++) {
        if (uuid_compare(server->clients[i]->uuid, uuid))
            return server->clients[i];
    }
    return NULL;
}

roundtable_client_t *roundtable_server_get_client_by_username(
    roundtable_server_t *server, const char *username)
{
    for (size_t i = 0; i < server->client_count; i++) {
        if (strcmp(server->clients[i]->username, username) == 0)
            return server->clients[i];
    }
    return NULL;
}

roundtable_client_t *roundtable_server_create_client(
    roundtable_server_t *server, const char *username)
{
    roundtable_client_t *new_client = calloc(1, sizeof(roundtable_client_t));

    if (new_client == NULL)
        return NULL;
    uuid_copy(new_client->uuid, *uuid_generate());
    new_client->username = strdup(username);
    new_client->status = OFFLINE;
    roundtable_server_add_client(server, new_client);
    return new_client;
}

roundtable_client_t *get_client_from_json(
    roundtable_server_t *server, json_object_t *body, char *key)
{
    return roundtable_server_get_client_by_uuid(server,
        *uuid_from_string(((json_string_t *) json_object_get(body,
        key))->value));
}

roundtable_client_t *get_client_from_header(
    roundtable_server_t *server, request_t *request)
{
    char *uuid_str = NULL;

    if (!request_has_header(request, "Authorization"))
        return NULL;
    uuid_str = request_get_header(request, "Authorization");
    if (uuid_str == NULL || strlen(uuid_str) != strlen("Bearer ") + 32)
        return NULL;
    return roundtable_server_get_client_by_uuid(server,
        *uuid_from_string(uuid_str + strlen("Bearer ")));
}
