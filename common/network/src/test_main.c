/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <stdio.h>
#include "network/router.h"

static response_t test_handler(request_t *req, void *data)
{
    return (response_t) {200, "OK", NULL, 0, ""};
}

int main(int argc, char **argv)
{
    router_t *router = NULL;

    if (argc != 2)
        return 84;
    router = router_init((host_t) {"127.0.0.1", atoi(argv[1])});
    if (router == NULL)
        return 84;
    router_add_route(router, "/test", &test_handler, NULL);
    router_start(router);
    return 0;
}
