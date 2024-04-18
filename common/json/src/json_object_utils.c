/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/json.h"
#include <string.h>

bool json_object_has_key(json_object_t *object, const char *key)
{
    for (size_t i = 0; i < object->size; i++) {
        if (strcmp(object->values[i]->key, key) == 0) {
            return true;
        }
    }
    return false;
}
