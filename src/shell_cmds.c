#include "shell_cmds.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

// gets user input and splits it up into 2 string arrays which are stored in the userInput struct
void getUserInput(struct userInput* input) {

    input->commands = malloc(MAX_CMD_AMOUNT * sizeof(char *));

    // initializes values for getline
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // reads user input
    printf("shelf-steam> ");
    fflush(stdout); // ensures shell line is shown before anything else
    read = getline(&line, &len, stdin);

    // jumps to start of while loop if string only contains white spaces
    if (isAllWhitespace(line)) {
        longjmp(errorJump, 1); // chars are all whitespace (not considered an error)
    }

    // ensures the inputted string fits within the max allowed string length
    if (read > MAX_CMD_LENGTH) {
        line[MAX_CMD_LENGTH + 1] = '\0';
    }

    int i = 0;
    char *token;
    char *line_ptr = line; // uses pointer so line can be freed later
    input->is_redirect = false; // assume no redirects before checking
    bool redirect_error_detect = false; // used to detect if there are 2 redirects
    while ((token = strsep(&line_ptr, " \t\n")) != NULL) {
        // continues if token is not the end of a string
        if (*token == '\0') {
            continue;
        }

        // if the "<" operator is seen, the next user input is a redirection
        if (!strcmp(token, "<")) {

            // error if user types the "<" operator more than once
            if (input->is_redirect) {
                handleError(0);
            }

            input->is_redirect = true;
            input->commands_size = i; // keeps track of commands array size
            i = 0;
            continue;
        }

        // saves redirect
        else if (input->is_redirect) {

            // error if user types 2 redirects or redirect is the "<" operator
            if (redirect_error_detect) {
                handleError(0);
            }

            strncpy(input->redirect, token, MAX_CMD_LENGTH);
            redirect_error_detect = true;
        }
        
        // cmd is saved in array
        else {
            input->commands[i] = malloc(strlen(token) + 1);
            strcpy(input->commands[i], token);
        }

        i++;
    }

    // error if no redirect was specified after the "<" operand
    if (!redirect_error_detect && input->is_redirect) {
        handleError(0);
    }

    if (!input->is_redirect) {
        input->commands_size = i; // keeps track of commands array size
    }

    input->commands[input->commands_size] = NULL; // adds NULL to the end of the commands for easier use of execvp later

    free(line);
}


// prints all games and their infos
void lsCommand(char *dir) {

    DIR *dir_ptr = opendir(dir);  // opens directory
    if (dir_ptr == NULL) {
        return;
    }

    struct dirent *entry;
    struct dirent **entries = NULL;
    int count = 0;

    // counts the number of entries
    while ((entry = readdir(dir_ptr)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            entries = realloc(entries, sizeof(struct dirent *) * (count + 1));
            entries[count] = entry;
            count++;
        }
    }

    // sorts them lexicographically
    qsort(entries, count, sizeof(struct dirent *), compareEntries);

    // print all files and their info
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            // ignores hidden metadata files (in this case for macOS)
            if (!strcmp(entries[i]->d_name, ".DS_Store")) {
                continue;
            }

            printf("%s: ", entries[i]->d_name);
            fflush(stdout); // ensures output is shown before process starts

            char *args[1024] = {entries[i]->d_name, "--help"};
            runProcess(dir, args, false, "", true);
        }
    }

    free(entries);
    closedir(dir_ptr);
}

// used to launch a game or replay a recorded game
void launchGame(char *dir, char **commands, bool is_redirect, const char *redirect) {
    runProcess(dir, commands, is_redirect, redirect, false); // runs the game
}

void handleError(bool is_exit) {
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
    fflush(stdout);

    // exits the program
    if (is_exit) {
        exit(1);
    }

    longjmp(errorJump, 1); // jumps to the start of the while loop
}