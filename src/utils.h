#ifndef UTILS_H
#define UTILS_H

#include "config.h"

void printInput(struct userInput* input);

void strcatReplace(char str1[PATH_MAX + 1], char replace[PATH_MAX + 1]);

int compareEntries(const void *a, const void *b);

#endif