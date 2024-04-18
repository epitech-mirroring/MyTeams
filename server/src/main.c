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

void bind_middlewares(roundtable_server_t *server)
{
}

void bind_routes(roundtable_server_t *server)
{
    router_add_route(server->router, "/login", login_route, server);
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
    bind_middlewares(server);
    bind_routes(server);
    get_server(true, server);
    sigaction(SIGINT, &(struct sigaction){.sa_handler = &stop}, NULL);
    router_start(server->router);
    save_data(server, "./data.json");
    destroy_server(server);
    return 0;
}
