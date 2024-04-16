/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"

void roundtable_channel_add_thread(roundtable_channel_t *channel,
    roundtable_thread_t *thread)
{
    roundtable_thread_t *new_threads = NULL;

    new_threads = realloc(channel->threads,
        sizeof(roundtable_thread_t) * (channel->thread_count + 1));
    if (new_threads == NULL)
        return;
    channel->threads = new_threads;
    channel->threads[channel->thread_count] = *thread;
    channel->thread_count++;
}
