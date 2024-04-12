/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "network/router.h"


char *response_to_string(response_t *response)
{
    char *response_str = malloc(sizeof(char) * (response->header.content_length + sizeof(response->header) + 1));

    sprintf(response_str, "%c%c%c%c%c%c%c%c%c%c%c%c%s", response->header.status_code & 0xFF,
            response->header.status_code >> 8 & 0xFF,
            response->header.status_code >> 16 & 0xFF,
            response->header.status_code >> 24 & 0xFF,
            (char)(response->header.content_length & 0xFF),
            (char)(response->header.content_length >> 8 & 0xFF),
            (char)(response->header.content_length >> 16 & 0xFF),
            (char)(response->header.content_length >> 24 & 0xFF),
            (char)(response->header.content_length >> 32 & 0xFF),
            (char)(response->header.content_length >> 40 & 0xFF),
            (char)(response->header.content_length >> 48 & 0xFF),
            (char)(response->header.content_length >> 56 & 0xFF),
            response->body);
    return response_str;
}


void router_send_response(int client_socket, void *data)
{
    response_t *response = (response_t *)data;
    char *response_str = response_to_string(response);

    write(client_socket, response_str, response->header.content_length);
    close(client_socket);
    free(response_str);
    free(response->body);
    free(response);
}