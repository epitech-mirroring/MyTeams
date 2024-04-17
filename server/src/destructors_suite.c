/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"


static void destroy_clients(roundtable_client_t *clients, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        destroy_client(clients[i]);
    }
    free(clients);
}

static void destroy_teams(roundtable_team_t *teams, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        destroy_team(teams[i]);
    }
    free(teams);
}

static void destroy_messages(roundtable_message_t *messages, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        destroy_message(messages[i]);
    }
    free(messages);
}

static void destroy_direct_messages(
    roundtable_direct_message_t *direct_messages, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        destroy_messages(direct_messages[i].messages,
            direct_messages[i].message_count);
    }
    free(direct_messages);
}

void destroy_thread(roundtable_thread_t thread)
{
    free(thread.title);
    free(thread.content);
    destroy_messages(thread.messages, thread.message_count);
}

void destroy_server(roundtable_server_t *server)
{
    if (!server)
        return;
    destroy_clients(server->clients, server->client_count);
    destroy_teams(server->teams, server->team_count);
    destroy_direct_messages(server->direct_messages, server->message_count);
    network_router_destroy(server->router);
    free(server);
}
