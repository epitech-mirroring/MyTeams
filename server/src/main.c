/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <unistd.h>
#include <sys/unistd.h>
#include "server.h"
#include "server_data.h"

int main(int ac, char **av)
{
    roundtable_server_t *server = create_server();

    (void) ac;
    (void) av;
    if (!server)
        return 84;
    if (access("./data.json", F_OK) != -1)
        load_data(server, "./data.json");
    save_data(server, "./data.json");
    destroy_server(server);
    return 0;
}
