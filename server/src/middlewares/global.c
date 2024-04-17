/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "routes.h"

request_t *global_middleware(request_t *request, void *data)
{
    request->data = data;
    return request;
}
