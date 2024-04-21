/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** info
*/

#include "myclient.h"
#include "commands.h"
#include "logging_client.h"

void info(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len != 1) {
        printf("Usage: /info\n");
        return;
    }
    if (client->is_logged == false) {
        client_error_unauthorized();
        return;
    }
    if (client->context->team_uuid == NULL) {
        return info_user(client);
    }
    if (client->context->channel_uuid == NULL) {
        return info_team(client);
    }
    if (client->context->thread_uuid == NULL) {
        return info_channel(client);
    }
    info_thread(client);
}
