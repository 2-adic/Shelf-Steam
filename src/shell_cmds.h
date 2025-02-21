#ifndef SHELL_CMDS_H
#define SHELL_CMDS_H

#include "config.h"

#include <stdbool.h>

// receives input from users
void getUserInput(struct userInput* input);

// lists all files in lexicographical order
void lsCommand(char *dir);

// used to launch a game or replay a past game
void launchGame(char *dir, char **commands, bool is_redirect, const char *redirect);

// displays error from incorrect input
void handleError(bool is_exit);

#endif