/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <criterion/criterion.h>
#include "uuid/uuid.h"

Test(uuid, compare_empty)
{
    uuid_t uu1 = {0};
    uuid_t uu2 = {0};

    cr_assert_eq(uuid_compare(uu1, uu2), true);
}

Test(uuid, compare_same)
{
    uuid_t uu1 = {0};
    uuid_t uu2 = {0};

    for (int i = 0; i < 16; i++) {
        uu1[i] = i;
        uu2[i] = i;
    }
    cr_assert_eq(uuid_compare(uu1, uu2), true);
}

Test(uuid, compare_different)
{
    uuid_t uu1 = {0};
    uuid_t uu2 = {0};

    for (int i = 0; i < 16; i++) {
        uu1[i] = i;
        uu2[i] = i + 1;
    }
    cr_assert_eq(uuid_compare(uu1, uu2), false);
}
