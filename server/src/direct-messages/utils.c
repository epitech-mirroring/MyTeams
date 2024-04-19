/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

void roundtable_server_add_direct_message(roundtable_server_t *server,
    roundtable_direct_message_t *direct_message)
{
    roundtable_direct_message_t **new_direct_messages = NULL;

    new_direct_messages = realloc(server->direct_messages,
        sizeof(roundtable_direct_message_t *) * (server->message_count + 1));
    if (new_direct_messages == NULL)
        return;
    server->direct_messages = new_direct_messages;
    server->direct_messages[server->message_count] = direct_message;
    server->message_count++;
}

void roundtable_direct_message_add_message(
    roundtable_direct_message_t *direct_message,
    roundtable_message_t *message)
{
    roundtable_message_t *new_messages = NULL;

    new_messages = realloc(direct_message->messages,
        sizeof(roundtable_message_t) * (direct_message->message_count + 1));
    if (new_messages == NULL)
        return;
    direct_message->messages = new_messages;
    direct_message->messages[direct_message->message_count] = *message;
    direct_message->message_count++;
}
