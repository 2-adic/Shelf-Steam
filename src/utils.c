#include "utils.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>

// prints user arguments for testing purposes
void printInput(struct userInput* input) {
    printf("\nCommands: %d\n", input->commands_size);
    for (int j = 0; j < input->commands_size; j++) {
        printf("%d: %s\n", j, input->commands[j]);
    }

    printf("\nRedirects: %d\n", input->std_redirect_size);
    for (int j = 0; j < input->std_redirect_size; j++) {
        printf("%d: %s\n", j, input->std_redirect[j]);
    }

    if (input->std_redirect_size != 0) {
        printf("\n");
    }
}

// has strcat functionality, but replaces the second string
void strcatReplace(char str1[PATH_MAX + 1], char replace[PATH_MAX + 1]) {

    // swap strings
    char temp[PATH_MAX + 1];
    strcpy(temp, str1);
    strcpy(str1, replace);
    strcpy(replace, temp);

    strcat(replace, str1); // combines strings

    strcpy(str1, temp); // puts original string back
}

// qsort comparison function
int compareEntries(const void *a, const void *b) {
    return strcmp((*(struct dirent **)a)->d_name, (*(struct dirent **)b)->d_name);
}