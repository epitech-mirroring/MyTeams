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

Test(uuid, to_string)
{
    uuid_t uu = {0};

    for (int i = 0; i < 16; i++)
        uu[i] = i;
    cr_assert_str_eq(uuid_to_string(uu), "000102030405060708090a0b0c0d0e0f");
}

Test(uuid, from_string)
{
    uuid_t uu = {0};
    char *str = "000102030405060708090a0b0c0d0e0f";

    for (int i = 0; i < 16; i++)
        uu[i] = i;
    cr_assert_eq(uuid_compare(uu, uuid_from_string(str)), true);
}

Test(uuid, from_string_empty)
{
    uuid_t uu = {0};
    char *str = "";

    cr_assert_null(uuid_from_string(str));
}

Test(uuid, from_string_invalid)
{
    uuid_t uu = {0};
    char *str = "000102030405060708090a0b0c0d0e0";

    cr_assert_null(uuid_from_string(str));
}

Test(uuid, save_and_load)
{
    uuid_t uu = {0};
    uuid_t *loaded;
    char *str = NULL;

    for (int i = 0; i < 16; i++)
        uu[i] = i;
    str = uuid_to_string(uu);
    loaded = uuid_from_string(str);
    cr_assert_eq(uuid_compare(uu, loaded), true);
}
