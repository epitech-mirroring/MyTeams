/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** use
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

static void empty_context(client_t *client)
{
    client->context->team_uuid = NULL;
    client->context->channel_uuid = NULL;
    client->context->thread_uuid = NULL;
}

static void set_context(client_t *client, char **parsed_cmd)
{
    int len = tab_len(parsed_cmd);

    if (len > 1)
        client->context->team_uuid = strdup(parsed_cmd[1]);
    if (len > 2)
        client->context->channel_uuid = strdup(parsed_cmd[2]);
    if (len > 3)
        client->context->thread_uuid = strdup(parsed_cmd[3]);
}

void use(char **parsed_cmd, client_t *client)
{
    int len = tab_len(parsed_cmd);

    if (len > 4) {
        printf("Usage: /use ?[team_uuid] ?[channel_uuid] ?[thread_uuid]\n");
        return;
    }
    if (client->is_logged == false) {
        client_error_unauthorized();
        return;
    }
    empty_context(client);
    set_context(client, parsed_cmd);
    printf("CLI : Context set to %s %s %s\n", client->context->team_uuid,
    client->context->channel_uuid, client->context->thread_uuid);
}
