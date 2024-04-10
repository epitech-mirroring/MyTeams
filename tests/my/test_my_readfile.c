/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <criterion/criterion.h>
#include "my/my.h"

#define test Test

test(my_readfile, simple_read)
{
    size_t size = 0;
    char *content = my_readfile("../../tests/my/files/one_char.txt", &size);

    cr_assert_not_null(content);
    cr_assert_eq(size, 1);
    cr_assert_str_eq(content, "a");
}

test(my_readfile, empty_file)
{
    size_t size = 0;
    char *content = my_readfile("../../tests/my/files/empty.txt", &size);

    cr_assert_not_null(content);
    cr_assert_eq(size, 0);
    cr_assert_str_eq(content, "");
}

test(my_readfile, file_not_found)
{
    size_t size = 0;
    char *content = my_readfile("../../tests/my/files/does_not_exist.txt", &size);

    cr_assert_null(content);
    cr_assert_eq(size, 0);
}

test(my_readfile, multiple_lines)
{
    size_t size = 0;
    char *content = my_readfile("../../tests/my/files/multiple_lines.txt", &size);

    cr_assert_not_null(content);
    cr_assert_eq(size, 24);
    cr_assert_str_eq(content, "line1\nline2\nline3\nline4\n");
}
