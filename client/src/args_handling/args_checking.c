/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** args_handling
*/

#include "myclient.h"

static bool is_valid_ip(char *ip)
{
    int dots = 0;
    int digits = 0;

    for (size_t i = 0; ip[i]; i++) {
        if (ip[i] == '.' && digits > 0) {
            dots++;
            digits = 0;
            continue;
        }
        if (ip[i] < '0' || ip[i] > '9')
            return false;
        digits++;
        if (digits > 3)
            return false;
    }
    return dots == 3 && digits > 0;
}

static bool is_valid_port(char *port)
{
    for (int i = 0; port[i]; i++) {
        if (port[i] < '0' || port[i] > '9')
            return false;
    }
    return true;
}

void print_help(void)
{
    printf("USAGE: ./myteams_cli ip port\n\n");
    printf("\tip\tis the server ip address on which the server "
        "socket listens\n");
    printf("\tport\tis the port number on which the server socket listens\n");
}

int is_valid_args(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return 84;
    if (ac != 3) {
        printf("Invalid number of arguments\n\n");
        return 84;
    }
    if (!is_valid_ip(av[1])) {
        printf("Invalid IP address\n\n");
        return 84;
    }
    if (!is_valid_port(av[2])) {
        printf("Invalid port number\n\n");
        return 84;
    }
    return 0;
}
