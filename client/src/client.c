/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** client
*/

#include "myclient.h"

static void reset_fd_set(fd_set *readfds, int fd)
{
    FD_ZERO(readfds);
    FD_SET(fd, readfds);
}

static client_t *init_struct(api_handler_t *api_handler)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL) {
        perror("malloc");
        exit(84);
    }
    client->is_logged = false;
    client->user_name = NULL;
    client->user_uuid = NULL;
    client->context = malloc(sizeof(context_t));
    if (client->context == NULL) {
        perror("malloc");
        exit(84);
    }
    client->context->team_uuid = NULL;
    client->context->channel_uuid = NULL;
    client->context->thread_uuid = NULL;
    client->api_handler = api_handler;
    return client;
}

static bool read_loop(int fd, char *cmd, bool *running, client_t *client)
{
    char buf[1];
    int status;

    status = read(fd, buf, 1);
    if (status == -1)
        exit(84);
    if (status == 0) {
        printf("Exiting client\n");
        *running = false;
        return false;
    }
    if (status != -1 && status != 0) {
        strncat(cmd, buf, 1);
        if (buf[0] == '\n') {
            on_command(cmd, client);
            memset(cmd, 0, 1024);
            return false;
        }
    }
    return true;
}

static void read_bytes(int fd, char *buffer, bool *running, client_t *client)
{
    char cmd[1024] = {0};

    strcpy(cmd, buffer);
    while (running) {
        if (!read_loop(fd, cmd, running, client))
            break;
    }
    memset(buffer, 0, 1024);
    strcpy(buffer, cmd);
}

void shell(client_t *client, fd_set readfds, char *buffer, bool *running)
{
    int select_ret;

    write(1, "> ", 2);
    reset_fd_set(&readfds, 0);
    select_ret = select(1, &readfds, NULL, NULL, NULL);
    if (select_ret == -1) {
        perror("select");
        exit(84);
    }
    if (select_ret > 0 && FD_ISSET(0, &readfds)) {
        read_bytes(0, buffer, running, client);
    } else if (select_ret == -1) {
        perror("select");
        exit(84);
    }
}

int main_loop(client_t *client)
{
    fd_set readfds;
    char buffer[1024] = {0};
    bool running = true;

    while (running) {
        if (client->waiting_for_response == false) {
            shell(client, readfds, buffer, &running);
        }
        if (client->api_handler->running)
            network_manager_handle_waiting_sockets(
                client->api_handler->manager);
    }
    return 0;
}

int client(int ac, char **av)
{
    client_t *client = NULL;
    host_t *host = malloc(sizeof(host_t));
    api_handler_t *api_handler = NULL;

    if (host == NULL) {
        return 84;
    }
    if (is_valid_args(ac, av) == 84) {
        print_help();
        return 84;
    }
    host->ip = strdup(av[1]);
    host->port = atoi(av[2]);
    api_handler = network_create_api_handler(host);
    if (api_handler == NULL) {
        return 84;
    }
    client = init_struct(api_handler);
    return main_loop(client);
}
