/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server_data.h"

json_object_t *serialize_client(roundtable_client_t *client)
{
    json_object_t *json = json_object_create(NULL);
    json_string_t *uuid = json_string_create("uuid",
        uuid_to_string(client->uuid));
    json_string_t *username = json_string_create("username", client->username);
    json_number_t *status = json_number_create("status", client->status);

    json_object_add(json, (json_t *) uuid);
    json_object_add(json, (json_t *) username);
    json_object_add(json, (json_t *) status);
    return json;
}
