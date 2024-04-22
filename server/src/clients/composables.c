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

static roundtable_client_instance_t *get_instance_from_strings(
    roundtable_server_t *server, char *uuid_str, char *instance_str)
{
    uuid_t *uuid = uuid_from_string(uuid_str);
    roundtable_client_t *client = NULL;
    size_t instance_number = 0;

    if (uuid == NULL)
        return NULL;
    client = roundtable_server_get_client_by_uuid(server, *uuid);
    if (client == NULL)
        return NULL;
    instance_number = atoi(instance_str);
    for (size_t i = 0; i < server->instance_count; i++) {
        if (server->instances[i]->instance_number == instance_number &&
            server->instances[i]->client == client)
            return server->instances[i];
    }
    return NULL;
}

roundtable_client_instance_t *get_instance_from_header(
    roundtable_server_t *server, request_t *request)
{
    char *header = NULL;
    char *uuid_str = NULL;
    char *instance_str = NULL;
    roundtable_client_instance_t *instance = NULL;

    if (!request_has_header(request, "Authorization"))
        return NULL;
    header = request_get_header(request, "Authorization");
    if (header == NULL)
        return NULL;
    uuid_str = strndup(header + strlen("Bearer "), 32);
    if (strlen(header) < strlen("Bearer ") + 32 + 2)
        return NULL;
    instance_str = header + strlen("Bearer ") + 32 + 1;
    instance = get_instance_from_strings(server, uuid_str, instance_str);
    free(uuid_str);
    return instance;
}
