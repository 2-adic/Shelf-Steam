#ifndef SHELL_CMDS_H
#define SHELL_CMDS_H

#include "config.h"

#include <stdbool.h>

// receives input from users
void getUserInput(struct userInput* input);

// lists all files in lexicographical order
void lsCommand(const char *dir_path);

// displays error from incorrect input
void handleError(bool is_exit);

#endif