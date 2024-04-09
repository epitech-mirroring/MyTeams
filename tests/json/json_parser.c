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

static bool is_equal(double a, double b) {
    if (a > b && a - b <= 0.0001)
        return true;
    if (b < a && b - a <= 0.0001)
        return true;
    if (b == a)
        return true;
    return false;
}

Test(json_parser, empty_file)
{
    // Create an empty file
    FILE *file = fopen("../../tests/json/empty.json", "wr");
    fwrite("{}", 1, 2, file);
    fclose(file);

    // Parse the file
    json_t *json = json_load_from_file("../../tests/json/empty.json");
    // Check if the file is empty
    cr_assert(json->type == JSON_OBJECT_TYPE_OBJECT);
    cr_assert_str_eq(json->key, "root");
    cr_assert(((json_object_t *) json)->values[0] == NULL);

    json_destroy(json);
    // Delete the file
    remove("../../tests/json/empty.json");
}

Test(json_parser, simple_file)
{
    // Create a simple file
    FILE *file = fopen("../../tests/json/simple.json", "wr");
    char *str = "{\"key\": \"value\"}";
    fwrite(str, 1, strlen(str), file);
    fclose(file);

    // Parse the file
    json_t *json = json_load_from_file("../../tests/json/simple.json");
    // Check if the file is correct
    cr_assert(json->type == JSON_OBJECT_TYPE_OBJECT);
    cr_assert_str_eq(json->key, "root");
    json_object_t *as_object = (json_object_t *) json;

    // Get the first object
    json_t *obj = json_object_get(as_object, "key");
    cr_assert(obj != NULL);
    cr_assert(obj->type == JSON_OBJECT_TYPE_STRING);
    cr_assert_str_eq(obj->key, "key");
    cr_assert_str_eq(((json_string_t *) obj)->value, "value");

    json_destroy(json);
    // Delete the file
    remove("../../tests/json/simple.json");
}

Test(json_parser, simple_obj_all_types)
{
    // Create a simple file with all types
    FILE *file = fopen("../../tests/json/simple_obj_all_types.json", "wr");
    char *str = "{\"str\": \"value\", \"int\": 42, \"bool\": true, \"null\": null, \"float\": 42.42}";
    fwrite(str, 1, strlen(str), file);
    fclose(file);

    // Parse the file
    json_t *json = json_load_from_file("../../tests/json/simple_obj_all_types.json");
    // Check if the file is correct
    cr_assert(json->type == JSON_OBJECT_TYPE_OBJECT);
    // String
    json_string_t *objS = (json_string_t *) json_object_get((json_object_t *) json, "str");
    cr_assert(objS != NULL);
    cr_assert(objS->base.type == JSON_OBJECT_TYPE_STRING);
    cr_assert_str_eq(objS->base.key, "str");
    cr_assert_str_eq(objS->value, "value");

    // Int
    json_number_t *objI = (json_number_t *) json_object_get((json_object_t *) json, "int");
    cr_assert(objI != NULL);
    cr_assert(objI->base.type == JSON_OBJECT_TYPE_NUMBER);
    cr_assert_str_eq(objI->base.key, "int");
    cr_assert_eq(objI->value, 42);

    // Bool
    json_boolean_t *objB = (json_boolean_t *) json_object_get((json_object_t *) json, "bool");
    cr_assert(objB != NULL);
    cr_assert(objB->base.type == JSON_OBJECT_TYPE_BOOLEAN);
    cr_assert_str_eq(objB->base.key, "bool");
    cr_assert_eq(objB->value, true);

    // Null
    json_null_t *objN = (json_null_t *) json_object_get((json_object_t *) json, "null");
    cr_assert(objN != NULL);
    cr_assert(objN->base.type == JSON_OBJECT_TYPE_NULL);
    cr_assert_str_eq(objN->base.key, "null");

    // Float
    json_float_t *objF = (json_float_t *) json_object_get((json_object_t *) json, "float");
    cr_assert(objF != NULL);
    cr_assert(objF->base.type == JSON_OBJECT_TYPE_FLOAT);
    cr_assert_str_eq(objF->base.key, "float");
    cr_assert(is_equal(objF->value, 42.42f));

    json_destroy(json);
    // Delete the file
    remove("../../tests/json/simple_obj_all_types.json");
}

Test(json_parser, object_in_object)
{
    // Create a file that contains an object in an object
    FILE *file = fopen("../../tests/json/object_in_object.json", "wr");
    char *str = "{\"key\": {\"key2\": \"value\"}}";
    fwrite(str, 1, strlen(str), file);
    fclose(file);

    // Parse the file
    json_t *json = json_load_from_file("../../tests/json/object_in_object.json");
    // Check if the file is correct
    cr_assert(json->type == JSON_OBJECT_TYPE_OBJECT);

    // Get the first object
    json_object_t *obj = (json_object_t *) json_object_get((json_object_t *) json, "key");
    cr_assert(obj != NULL);
    cr_assert(obj->base.type == JSON_OBJECT_TYPE_OBJECT);
    // Get the content of the object
    json_string_t *obj2 = (json_string_t *) json_object_get(obj, "key2");
    cr_assert(obj2 != NULL);
    cr_assert(obj2->base.type == JSON_OBJECT_TYPE_STRING);
    cr_assert_str_eq(obj2->base.key, "key2");
    cr_assert_str_eq(obj2->value, "value");

    json_destroy(json);
    // Delete the file
    remove("../../tests/json/object_in_object.json");
}

Test(json_parser, array_in_object) {
    // Create a file that contains an array in an object
    FILE *file = fopen("../../tests/json/array_in_object.json", "wr");
    char *str = "{\"key\": [\"value\", 42, true, null]}";
    fwrite(str, 1, strlen(str), file);
    fclose(file);

    // Parse the file
    json_t *json = json_load_from_file("../../tests/json/array_in_object.json");
    // Check if the file is correct
    cr_assert(json->type == JSON_OBJECT_TYPE_OBJECT);

    // Get the array
    json_array_t *arr = (json_array_t *) json_object_get((json_object_t *) json, "key");
    cr_assert(arr != NULL);
    cr_assert(arr->base.type == JSON_OBJECT_TYPE_ARRAY);
    cr_assert_eq(arr->size, 4);

    // Get the first element
    json_string_t *s = (json_string_t *) json_array_get(arr, 0);
    cr_assert(s != NULL);
    cr_assert(s->base.type == JSON_OBJECT_TYPE_STRING);
    cr_assert_str_eq(s->value, "value");

    // Get the second element
    json_number_t *i = (json_number_t *) json_array_get(arr, 1);
    cr_assert(i != NULL);
    cr_assert(i->base.type == JSON_OBJECT_TYPE_NUMBER);
    cr_assert_eq(i->value, 42);

    // Get the third element
    json_boolean_t *b = (json_boolean_t *) json_array_get(arr, 2);
    cr_assert(b != NULL);
    cr_assert(b->base.type == JSON_OBJECT_TYPE_BOOLEAN);
    cr_assert_eq(b->value, true);

    // Get the fourth element
    json_null_t *n = (json_null_t *) json_array_get(arr, 3);
    cr_assert(n != NULL);
    cr_assert(n->base.type == JSON_OBJECT_TYPE_NULL);

    json_destroy(json);
    // Delete the file
    remove("../../tests/json/array_in_object.json");
}


Test(json_parser, json_obj_in_array)
{
    // Create a file that contains an object in an array
    FILE *file = fopen("../../tests/json/json_obj_in_array.json", "wr");
    char *str = "{\"array\": [{\"key\": \"value\"}]}";
    fwrite(str, 1, strlen(str), file);
    fclose(file);

    // Parse the file
    json_t *json = json_load_from_file("../../tests/json/json_obj_in_array.json");
    // Check if the file is correct
    cr_assert(json->type == JSON_OBJECT_TYPE_OBJECT);

    // Get the array
    json_array_t *arr = (json_array_t *) json_object_get((json_object_t *) json, "array");
    cr_assert(arr != NULL);
    cr_assert(arr->base.type == JSON_OBJECT_TYPE_ARRAY);
    cr_assert_eq(arr->size, 1);

    // Get the first element
    json_object_t *obj = (json_object_t *) json_array_get(arr, 0);
    cr_assert(obj != NULL);
    cr_assert(obj->base.type == JSON_OBJECT_TYPE_OBJECT);

    // Get the content of the object
    json_string_t *value = (json_string_t *) json_object_get(obj, "key");
    cr_assert(value != NULL);
    cr_assert(value->base.type == JSON_OBJECT_TYPE_STRING);
    cr_assert_str_eq(value->value, "value");

    json_destroy(json);
    // Delete the file
    remove("../../tests/json/json_obj_in_array.json");
}

Test(json_parser, json_root_array)
{
    // Create a file that contains an object in an array
    FILE *file = fopen("../../tests/json/json_root_array.json", "wr");
    char *str = "[\"value\", 42, true, null]";
    fwrite(str, 1, strlen(str), file);
    fclose(file);

    // Parse the file
    json_array_t *json = (json_array_t *) json_load_from_file("../../tests/json/json_root_array.json");
    // Check if the file is correct
    cr_assert(json->base.type == JSON_OBJECT_TYPE_ARRAY);
    cr_assert_eq(json->size, 4);

    // Get the first element
    json_string_t *jsonString = (json_string_t *) json_array_get(json, 0);
    cr_assert(jsonString != NULL);
    cr_assert(jsonString->base.type == JSON_OBJECT_TYPE_STRING);
    cr_assert_str_eq(jsonString->value, "value");

    // Get the second element
    json_number_t *jsonNumber = (json_number_t *) json_array_get(json, 1);
    cr_assert(jsonNumber != NULL);
    cr_assert(jsonNumber->base.type == JSON_OBJECT_TYPE_NUMBER);
    cr_assert_eq(jsonNumber->value, 42);

    // Get the third element
    json_boolean_t *jsonBoolean = (json_boolean_t *) json_array_get(json, 2);
    cr_assert(jsonBoolean != NULL);
    cr_assert(jsonBoolean->base.type == JSON_OBJECT_TYPE_BOOLEAN);
    cr_assert_eq(jsonBoolean->value, true);

    // Get the fourth element
    json_null_t *jsonNull = (json_null_t *) json_array_get(json, 3);
    cr_assert(jsonNull != NULL);
    cr_assert(jsonNull->base.type == JSON_OBJECT_TYPE_NULL);

    json_destroy((json_t *) json);
    // Delete the file
    remove("../../tests/json/json_root_array.json");
}

Test(json_parser, json_empty_array)
{
    FILE *file = fopen("../../tests/json/json_empty_array.json", "wr");
    fwrite("[]", 1, 2, file);
    fclose(file);

    // Parse the file
    json_array_t *json = (json_array_t *) json_load_from_file("../../tests/json/json_empty_array.json");
    // Check if the file is correct
    cr_assert(json->base.type == JSON_OBJECT_TYPE_ARRAY);
    cr_assert_eq(json->size, 0);

    json_destroy((json_t *) json);
    // Delete the file
    remove("../../tests/json/json_empty_array.json");
}
