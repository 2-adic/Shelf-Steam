#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <setjmp.h>

extern jmp_buf errorJump; // used for error handling to jump to the start of the while loop

#define PATH_MAX 4096
#define MAX_CMD_AMOUNT 128
#define MAX_CMD_LENGTH 255

// used to store user input
struct userInput {
    char **commands;
    char redirect[MAX_CMD_LENGTH + 1];

    int commands_size;
    bool is_redirect;
};

#endif