/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** *
*/

#include "myclient.h"
#include "logging_client.h"

void logged_in_callback(json_object_t *data, client_t *client)
{
    json_string_t *user_uuid =
        (json_string_t *)json_object_get(data, "user_uuid");
    json_string_t *username =
        (json_string_t *)json_object_get(data, "username");

    if (user_uuid == NULL || username == NULL)
        return;
    client_event_logged_in(user_uuid->value, username->value);
}
