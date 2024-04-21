/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list
*/

#include "myclient.h"
#include "commands.h"
#include "logging_client.h"

void list(char **parsed_cmd, client_t *client)
{
    if (tab_len(parsed_cmd) != 1) {
        printf("Usage: /list\n");
        return;
    }
    if (client->is_logged == false) {
        client_error_unauthorized();
        return;
    }
    if (client->context->team_uuid == NULL) {
        return list_teams(client);
    }
    if (client->context->channel_uuid == NULL) {
        return list_channels(client);
    }
    if (client->context->thread_uuid == NULL) {
        return list_threads(client);
    }
    list_replies(client);
}
