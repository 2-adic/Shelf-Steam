#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <setjmp.h>

jmp_buf errorJump;

#define PATH_MAX 4096
#define MAX_CMD_AMOUNT 128
#define MAX_CMD_LENGTH 255

struct userInput {
    char **commands;
    char redirect[MAX_CMD_LENGTH + 1];

    int commands_size;
    bool is_redirect;
};

#endif