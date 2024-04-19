/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include "server.h"
#include "server_utils.h"
#include "network/dto.h"

static bool body_is_valid(json_object_t *body)
{
    bool name = json_object_has_key(body, "name");
    bool description = json_object_has_key(body, "description");

    return name && description;
}

static const char *get_missing_key(json_object_t *body)
{
    if (body == NULL)
        return "Missing 'name' and 'description'";
    if (!json_object_has_key(body, "name"))
        return "Missing 'name'";
    if (!json_object_has_key(body, "description"))
        return "Missing 'description'";
    return NULL;
}

static response_t create_team_response(roundtable_team_t *team)
{
    json_object_t *body = json_object_create(NULL);
    char *body_str = NULL;
    response_t response;

    json_object_add(body, (json_t *) json_string_create("team_uuid",
        uuid_to_string(team->uuid)));
    body_str = json_serialize((json_t *) body);
    json_object_destroy(body);
    response = create_success(201, body_str);
    free(body_str);
    return response;
}

response_t create_team_route(request_t *request, void *data)
{
    roundtable_server_t *server = (roundtable_server_t *) data;
    json_object_t *body = (json_object_t *) json_parse(request->body);
    roundtable_client_t *client = NULL;
    roundtable_team_t *team = NULL;

    if (strcmp(request->route.method, "POST") != 0)
        return create_error(405, "Method not allowed", "Only POST");
    if (!request_has_header(request, "Authorization"))
        return create_error(401, "Unauthorized", "Missing 'Authorization'");
    if (body == NULL || !body_is_valid(body))
        return create_error(400, "Invalid body", get_missing_key(body));
    client = get_client_from_header(server, request);
    if (!client)
        return create_error(401, "Unauthorized", "Invalid 'Authorization'");
    team = roundtable_server_create_team(server,
        ((json_string_t *) json_object_get(body, "name"))->value,
        ((json_string_t *) json_object_get(body, "description"))->value);
    if (!team)
        return create_error(500, "Internal server error",
            "Team creation failed");
    return create_team_response(team);
}
