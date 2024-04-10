/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "network_types.h"

network_router_t *network_router_create(void);
void network_router_destroy(network_router_t *router);

void network_router_add_route(network_router_t *router, route_t *route, route_handler_t handler);
void network_router_remove_route(network_router_t *router, route_t *route);

void network_router_listen();
