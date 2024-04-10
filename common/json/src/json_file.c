/*
** EPITECH PROJECT, 2024
** json
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "json/json.h"
#include "my/my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

json_t *json_load_from_file(const char *path)
{
    json_t *json = NULL;
    size_t size = 0;
    char *content = my_readfile(path, &size);

    if (content == NULL) {
        fprintf(stderr, "Failed to read file %s\n", path);
        return NULL;
    }
    json = json_parse(content);
    free(content);
    return json;
}

void json_save_to_file(json_t *json, const char *path)
{
    char *content = json_serialize(json);
    FILE *file = NULL;

    if (content == NULL) {
        fprintf(stderr, "Failed to convert json to string\n");
        return;
    }
    file = fopen(path, "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file %s\n", path);
        free(content);
        return;
    }
    fwrite(content, strlen(content), 1, file);
    fclose(file);
    free(content);
}
