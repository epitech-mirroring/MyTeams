/*
** EPITECH PROJECT, 2023
** B-MUL-100-NAN-1-1-myradar-axel.eckenberg
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "my/my.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char *my_readfile(char const *filepath, size_t *size)
{
    int fd = open(filepath, O_RDONLY);
    char *buffer = NULL;

    if (fd == -1)
        return NULL;
    buffer = malloc(sizeof(char) * 1);
    *size = 0;
    while (read(fd, buffer, 1) > 0)
        (*size)++;
    close(fd);
    free(buffer);
    buffer = malloc(sizeof(char) * (*size + 1));
    fd = open(filepath, O_RDONLY);
    read(fd, buffer, *size);
    buffer[*size] = '\0';
    return buffer;
}
