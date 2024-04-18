/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "network/sockets.h"

int socket_create_client(host_t host)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in s_in;

    if (socket_fd == -1)
        return -1;
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(host.port);
    s_in.sin_addr.s_addr = inet_addr(host.ip);
    if (connect(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
        return -1;
    return socket_fd;
}

int socket_create_server(host_t host)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    int opt = 1;

    if (sock == -1)
        return -1;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(host.port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1 ||
        bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1 ||
        listen(sock, 10) == -1)
        return 0;
    return sock;
}
