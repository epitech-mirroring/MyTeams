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

roundtable_client_instance_t **roundtable_client_instances_find(
    roundtable_server_t *server, roundtable_client_t *client)
{
    roundtable_client_instance_t **instances =
        calloc(1, sizeof(roundtable_client_instance_t *));
    size_t instance_count = 0;

    for (size_t i = 0; i < server->instance_count; i++) {
        if (uuid_compare(server->instances[i]->client->uuid, client->uuid)) {
            instances = realloc(instances,
                sizeof(roundtable_client_instance_t *) * (instance_count + 1));
            instances[instance_count] = server->instances[i];
            instance_count++;
        }
    }
    return instances;
}

size_t get_instance_count(roundtable_server_t *server,
    roundtable_client_t *client)
{
    size_t instance_count = 0;

    for (size_t i = 0; i < server->instance_count; i++) {
        if (uuid_compare(server->instances[i]->client->uuid, client->uuid)) {
            instance_count++;
        }
    }
    return instance_count;
}

static void add_instance_to_server(roundtable_server_t *server,
    roundtable_client_instance_t *instance)
{
    roundtable_client_instance_t **new_instances =
        realloc(server->instances, sizeof(roundtable_client_instance_t *) *
            (server->instance_count + 1));

    if (new_instances == NULL)
        return;
    server->instances = new_instances;
    server->instances[server->instance_count] = instance;
    server->instance_count++;
}

void roundtable_client_instance_remove(roundtable_server_t *server,
    roundtable_client_instance_t *instance)
{
    roundtable_client_instance_t **new_instances =
        calloc(1, sizeof(roundtable_client_instance_t *));
    size_t instance_count = 0;

    for (size_t i = 0; i < server->instance_count; i++) {
        if (server->instances[i] != instance) {
            new_instances = realloc(new_instances,
                sizeof(roundtable_client_instance_t *) * (instance_count + 1));
            new_instances[instance_count] = server->instances[i];
            instance_count++;
        }
    }
    free(server->instances);
    server->instances = new_instances;
    server->instance_count = instance_count;
    destroy_instance(instance);
}

roundtable_client_instance_t *roundtable_client_instance_create(
    roundtable_server_t *server, roundtable_client_t *client)
{
    roundtable_client_instance_t *new_instance =
        calloc(1, sizeof(roundtable_client_instance_t));
    size_t instance_count = get_instance_count(server, client);

    if (new_instance == NULL)
        return NULL;
    new_instance->client = client;
    new_instance->events = calloc(1, sizeof(events_t *));
    new_instance->event_count = 0;
    new_instance->instance_number = instance_count + 1;
    add_instance_to_server(server, new_instance);
    return new_instance;
}
