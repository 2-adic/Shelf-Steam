#ifndef CONFIG_H
#define CONFIG_H

#define PATH_MAX 4096
#define MAX_CMD_AMOUNT 128
#define MAX_CMD_LENGTH 255

struct userInput {
    char commands[MAX_CMD_AMOUNT][MAX_CMD_LENGTH + 1];
    char std_redirect[MAX_CMD_AMOUNT][MAX_CMD_LENGTH + 1];

    int commands_size;
    int std_redirect_size;
};

#endif