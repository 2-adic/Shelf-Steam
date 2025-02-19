#ifndef SHELL_CMDS_H
#define SHELL_CMDS_H

#include "config.h"

#include <stdbool.h>

// receives input from users
void getUserInput(struct userInput* input);

// lists all files in lexicographical order
void lsCommand(const char *dir_path);

// used to launch a game or replay a past game
void launchGame(char dir[PATH_MAX + 1], char **commands, bool is_redirect, char redirect[MAX_CMD_LENGTH + 1]);

// displays error from incorrect input
void handleError(bool is_exit);

#endif