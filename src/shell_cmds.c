#include "shell_cmds.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

// gets user input and splits it up into 2 string arrays which are stored in the userInput struct
void getUserInput(struct userInput* input) {

    // initializes values for getline
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // reads user input
    printf("shelf-steam> ");
    read = getline(&line, &len, stdin);

    // ensures the inputted string fits within the max allow string length
    if (read > MAX_CMD_LENGTH) {
        line[MAX_CMD_LENGTH] = '\0';
    }

    int i = 0;
    char *token;
    char *line_ptr = line; // uses pointer so line can be freed later
    bool is_redirect = false; // keeps track if the "<" symbols has been seen
    while ((token = strsep(&line_ptr, " \t\n")) != NULL) {
        // continues if token is not the end of a string
        if (*token == '\0') {
            continue;
        }

        // if the "<" string is seen, the next user inputs are for input redirection
        if (!strcmp(token, "<")) {
            is_redirect = true;
            input->commands_size = i; // keeps track of commands array size
            i = 0;
            continue;
        }

        // if an input string is not a redirect, it is put in the commands array
        else if (!is_redirect) {
            strncpy(input->commands[i], token, MAX_CMD_LENGTH);
        }

        // if an input string is a redirect, it is put in the redirect array
        else if (is_redirect) {
            strncpy(input->std_redirect[i], token, MAX_CMD_LENGTH);
        }
        
        // stops reading if
        if (i >= MAX_CMD_AMOUNT) {
            break;
        }
        
        i++;
    }

    if (is_redirect) {
        input->std_redirect_size = i; // keeps track of std redirect array size
    }

    else {
        input->commands_size = i; // keeps track of commands array size
        input->std_redirect_size = 0; // keeps track of std redirect array size
    }

    free(line);
}

void lsCommand(const char *dir_path) {
    DIR *dir = opendir(dir_path);  // open directory
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    struct dirent **entries = NULL;
    int count = 0;

    // counts the number of entries
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            entries = realloc(entries, sizeof(struct dirent *) * (count + 1));
            entries[count] = entry;
            count++;
        }
    }

    // sorts them lexicographically
    qsort(entries, count, sizeof(struct dirent *), compareEntries);

    // prints the sorted entries
    for (int i = 0; i < count; i++) {
        printf("%s\n", entries[i]->d_name);
    }

    free(entries);
    closedir(dir);
}


void handleError(bool is_exit) {
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
    fflush(stdout);

    // exits the program
    if (is_exit) {
        exit(1);
    }
}