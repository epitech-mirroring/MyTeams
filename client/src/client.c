/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** client
*/

#include "myclient.h"
#include "commands.h"
#include "teams_events.h"
#include "logging_client.h"
#include "network/manager.h"
#include "network/sockets.h"
#include <sys/time.h>

static client_t *init_struct(api_client_t *api_handler)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL) {
        exit(84);
    }
    client->is_logged = false;
    client->waiting_for_response = false;
    client->running = true;
    client->buffer = calloc(1024, sizeof(char));
    client->user_name = NULL;
    client->user_uuid = NULL;
    client->context = malloc(sizeof(context_t));
    if (client->context == NULL || client->buffer == NULL) {
        exit(84);
    }
    client->context->team_uuid = NULL;
    client->context->channel_uuid = NULL;
    client->context->thread_uuid = NULL;
    client->api_handler = api_handler;
    return client;
}

static bool read_loop(int fd, char *cmd, client_t *client)
{
    char buf[1];
    long status;

    status = read(fd, buf, 1);
    if (status == -1)
        exit(84);
    if (status == 0) {
        printf("Exiting client\n");
        client->running = false;
        return false;
    }
    strncat(cmd, buf, 1);
    if (buf[0] == '\n') {
        on_command(cmd, client);
        memset(cmd, 0, 1024);
        return false;
    }
    return true;
}

static void read_bytes(int fd, char *buffer, client_t *client)
{
    char cmd[1024] = {0};

    strcpy(cmd, buffer);
    while (client->running) {
        if (!read_loop(fd, cmd, client))
            break;
    }
    memset(buffer, 0, 1024);
    strcpy(buffer, cmd);
}

bool callback(waiting_socket_t *socket)
{
    client_t *client = (client_t *)socket->data;

    if (client->waiting_for_response == false) {
        read_bytes(0, client->buffer, client);
    }
    return true;
}

static void send_running_events(client_t *client)
{
    struct timeval tv;
    long current_time = 0;
    static long client_time = 0;
    long time_spent = 0;

    gettimeofday(&tv, NULL);
    current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    time_spent = (current_time - client_time);
    if (time_spent >= TIME_BETWEEN_REQUESTS && client->is_event == false) {
        client_time = current_time;
        send_events(client);
    }
}

int main_loop(client_t *client)
{
    waiting_socket_t *ws = waiting_sockets_add_socket(
        client->api_handler->ws_manager->ws, 0, READ, &callback);

    ws->data = client;
    client->is_event = true;
    send_events(client);
    while (client->running) {
        send_running_events(client);
        ws_manager_run_once(client->api_handler->ws_manager);
    }
    if (client->is_logged == true) {
        logout_when_leaving(client);
        send_events(client);
    }
    while (client->user_uuid != NULL) {
        ws_manager_run_once(client->api_handler->ws_manager);
    }
    return 0;
}

int client(int ac, char **av)
{
    client_t *client = NULL;
    api_client_t *api_handler = NULL;

    if (is_valid_args(ac, av) == 84) {
        print_help();
        return 84;
    }
    api_handler = api_client_init(av[1], atoi(av[2]));
    if (api_handler == NULL) {
        return 84;
    }
    client = init_struct(api_handler);
    return main_loop(client);
}
