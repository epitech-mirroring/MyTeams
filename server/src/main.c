/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <unistd.h>
#include <sys/unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "server.h"
#include "server_data.h"
#include "routes.h"
#include "server_utils.h"

const roundtable_route_t ROUTES[] = {
    {"/login", login_route},
    {"/logout", logout_route},
    {"/messages/send", send_dm_route},
    {"/messages", get_dms_route},
    {"/teams/create", create_team_route},
    {"/teams", get_teams_route},
    {"/teams/join", join_team_route},
    {"/teams/leave", leave_team_route},
    {"/teams/users", team_users_route},
    {"/teams/channels/create", create_channel_route},
    {"/user", user_route},
    {"/users", users_route},
    {NULL, NULL}
};

void bind_routes(roundtable_server_t *s)
{
    for (size_t i = 0; ROUTES[i].path; i++)
        router_add_route(s->router, ROUTES[i].path, ROUTES[i].handler, s);
}

static roundtable_server_t *get_server(bool write, void *data)
{
    static roundtable_server_t *server = NULL;

    if (write)
        server = (roundtable_server_t *) data;
    return server;
}

static void stop(int sig)
{
    roundtable_server_t *server = get_server(false, NULL);

    (void)sig;
    if (server)
        server->router->ws_manager->running = false;
}

int main(int ac, char **av)
{
    roundtable_server_t *server = NULL;

    if (ac != 2)
        return 84;
    server = create_server((int) strtol(av[1], NULL, 10));
    if (!server)
        return 84;
    if (access("./data.json", F_OK) != -1)
        load_data(server, "./data.json");
    bind_routes(server);
    get_server(true, server);
    sigaction(SIGINT, &(struct sigaction){.sa_handler = &stop}, NULL);
    router_add_middleware(server->router, "/", &options_middleware, server);
    router_start(server->router);
    save_data(server, "./data.json");
    destroy_server(server);
    return 0;
}
