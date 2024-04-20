/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** info_user
*/

#include "myclient.h"
#include "logging_client.h"

void info_user(client_t *client)
{
    client_print_user(client->user_uuid, client->user_name, 1);
}
