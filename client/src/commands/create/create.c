/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** create
*/

#include "myclient.h"
#include "logging_client.h"
#include "json/json.h"

void create(char **parsed_cmd, client_t *client)
{
    if (client->is_logged == false) {
        client_error_unauthorized();
        return;
    }
    if (client->context->team_uuid == NULL) {
        return create_team(parsed_cmd, client);
    }
    if (client->context->channel_uuid == NULL) {
        return create_channel(parsed_cmd, client);
    }
    if (client->context->thread_uuid == NULL) {
        return create_thread(parsed_cmd, client);
    }
    create_reply(parsed_cmd, client);
}
