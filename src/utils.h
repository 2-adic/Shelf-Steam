#ifndef UTILS_H
#define UTILS_H

#include "config.h"
#include <stdbool.h>

void printInput(struct userInput* input);

void strcatReplace(char str1[PATH_MAX + 1], char replace[PATH_MAX + 1]);

int compareEntries(const void *a, const void *b);

bool isFileInDirectory(const char *filename, const char *dir);

void runProcess(char dir[PATH_MAX + 1], char **commands, bool is_redirect, char redirect[MAX_CMD_LENGTH + 1]);

#endif