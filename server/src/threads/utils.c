/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

void roundtable_thread_add_message(roundtable_thread_t *thread,
    roundtable_message_t *message)
{
    roundtable_message_t *new_messages = NULL;

    new_messages = realloc(thread->messages,
        sizeof(roundtable_message_t) * (thread->message_count + 1));
    if (new_messages == NULL)
        return;
    thread->messages = new_messages;
    thread->messages[thread->message_count] = *message;
    thread->message_count++;
}
