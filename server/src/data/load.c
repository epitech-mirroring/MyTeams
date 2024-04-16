/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server_data.h"

void load_data(roundtable_server_t *server, const char *path)
{
    json_object_t *json = (json_object_t *) json_load_from_file(path);

    if (json == NULL)
        return;
    deserialize_clients(server,
        (json_array_t *) json_object_get(json, "clients"));
    deserialize_teams(server,
        (json_array_t *) json_object_get(json, "teams"));
    deserialize_direct_messages(server,
        (json_array_t *) json_object_get(json, "direct_messages"));
    json_destroy((json_t *) json);
}
