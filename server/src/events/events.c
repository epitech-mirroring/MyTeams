/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

void roundtable_server_send_event(roundtable_server_t *server,
    roundtable_client_instance_t *instance, events_t *event)
{
    events_t **new_events = NULL;

    new_events = realloc(instance->events,
        sizeof(events_t *) * (instance->event_count + 1));
    if (new_events == NULL)
        return;
    instance->events = new_events;
    instance->events[instance->event_count] = event;
    instance->event_count++;
}

void roundtable_server_destroy_event(events_t *event)
{
    free(event);
}

void roundtable_server_clear_events(roundtable_server_t *server,
    roundtable_client_instance_t *client)
{
    for (size_t i = 0; i < client->event_count; i++) {
        roundtable_server_destroy_event(client->events[i]);
    }
    free(client->events);
    client->events = calloc(1, sizeof(events_t *));
    client->event_count = 0;
}

events_t *roundtable_server_create_event(events_type_t type,
    json_object_t *data)
{
    events_t *new_event = calloc(1, sizeof(events_t));

    if (new_event == NULL)
        return NULL;
    new_event->type = type;
    new_event->data = data;
    return new_event;
}
