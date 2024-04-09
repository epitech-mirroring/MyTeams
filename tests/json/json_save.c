/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/json.h"
#include <stdio.h>
#include <criterion/criterion.h>

Test(json_save, empty_json)
{
    json_object_t *json = json_object_create("root");
    json_save_to_file((json_t *) json, "../../tests/json/s_empty.json");
    json_destroy((json_t *) json);

    // Check if the file is present
    FILE *f1 = fopen("../../tests/json/s_empty.json", "r");
    cr_assert(f1 != NULL);

    // Check if the file only contains {"null": null}
    char *str = malloc(sizeof(char) * 100);
    int size = fread(str, 1, 100, f1);
    str[size] = '\0';
    cr_assert_str_eq(str, "{}");

    // Delete the file
    remove("../../tests/json/s_empty.json");
}

Test(json_save, simple_json)
{
    json_object_t *json = json_object_create("root");
    json_string_t *string = json_string_create("string", "value");
    json_number_t *integer = json_number_create("int", 42);
    json_boolean_t *boolean = json_boolean_create("bool", true);
    json_null_t *null = json_null_create("null");
    json_float_t *floating = json_float_create("float", 3.14f);
    json_object_add(json, (json_t *) string);
    json_object_add(json, (json_t *) integer);
    json_object_add(json, (json_t *) boolean);
    json_object_add(json, (json_t *) null);
    json_object_add(json, (json_t *) floating);
    json_save_to_file((json_t *) json, "../../tests/json/s_simple.json");
    json_destroy((json_t *) json);

    // Check if the file is present
    FILE *f1 = fopen("../../tests/json/s_simple.json", "r");
    cr_assert(f1 != NULL);

    // Check if the file only contains {"null": null}
    char *str = malloc(sizeof(char) * 105);
    int size = fread(str, 1, 105, f1);
    str[size] = '\0';
    cr_assert_str_geq(str, "{\"string\":\"value\",\"int\":42,\"bool\":true,\"null\":null,\"float\":3.1400");

    // Delete the file
    remove("../../tests/json/s_simple.json");
}

Test(json_save, array_of_int)
{
    json_array_t *array = json_array_create("root");
    json_number_t *int1 = json_number_create(NULL, 42);
    json_number_t *int2 = json_number_create(NULL, 43);
    json_number_t *int3 = json_number_create(NULL, 44);
    json_array_add(array, (json_t *) int1);
    json_array_add(array, (json_t *) int2);
    json_array_add(array, (json_t *) int3);
    json_save_to_file((json_t *) array, "../../tests/json/s_array_of_int.json");
    json_destroy((json_t *) array);

    // Check if the file is present
    FILE *f1 = fopen("../../tests/json/s_array_of_int.json", "r");
    cr_assert(f1 != NULL);

    // Check if the file only contains {"null": null}
    char *str = malloc(sizeof(char) * 105);
    int size = fread(str, 1, 105, f1);
    str[size] = '\0';
    cr_assert_str_eq(str, "[42,43,44]");

    // Delete the file
    remove("../../tests/json/s_array_of_int.json");
}

Test(json_save, obj_array)
{
    json_object_t *json = json_object_create("root");

    json_array_t *array = json_array_create("array");
    json_object_t *obj1 = json_object_create("obj1");
    json_object_t *obj2 = json_object_create("obj2");
    json_string_t *string = json_string_create("string", "value");
    json_number_t *integer = json_number_create("int", 42);
    json_object_add(obj1, (json_t *) string);
    json_object_add(obj2, (json_t *) integer);
    json_array_add(array, (json_t *) obj1);
    json_array_add(array, (json_t *) obj2);
    json_object_add(json, (json_t *) array);
    json_save_to_file((json_t *) json, "../../tests/json/s_obj_array.json");
    json_destroy((json_t *) json);

    // Check if the file is present
    FILE *f1 = fopen("../../tests/json/s_obj_array.json", "r");
    cr_assert(f1 != NULL);

    // Check if the file only contains
    char *str = malloc(sizeof(char) * 105);
    int size = fread(str, 1, 105, f1);
    str[size] = '\0';
    cr_assert_str_eq(str, "{\"array\":[{\"string\":\"value\"},{\"int\":42}]}");

    // Delete the file
    remove("../../tests/json/s_obj_array.json");
}