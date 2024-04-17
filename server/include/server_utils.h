/*
** EPITECH PROJECT, 2024
** server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "network/router.h"

// -------------------------- NETWORK --------------------------------
response_t *create_error(int status_code,
    const char *name, const char *message);
