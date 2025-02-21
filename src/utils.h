#ifndef UTILS_H
#define UTILS_H

#include "config.h"
#include <stdbool.h>

// prints user input for testing
void printInput(struct userInput* input);

// used for lexicographic sorting with qsort
int compareEntries(const void *a, const void *b);

// returns if a file is within a directory
bool isFileInDirectory(const char *filename, const char *dir);

// runs a given program as a process (forks the program to run the process)
void runProcess(char *dir, char **commands, bool is_redirect, const char *redirect, bool is_ls);

// returns if a string contains only white spaces (' ', '\n', '\t')
bool isAllWhitespace(const char *str);

// returns if a directory is found at the given path
bool isDirectoryValid(const char *dir);

#endif