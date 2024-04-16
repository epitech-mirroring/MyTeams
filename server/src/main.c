/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "server.h"
#include "server_data.h"

int main(int ac, char **av)
{
    roundtable_server_t *server = create_server();

    (void) ac;
    (void) av;
    if (!server)
        return 84;
    load_data(server, "./data.json");
    destroy_server(server);
    return 0;
}
