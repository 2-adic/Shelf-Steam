#include "shell.h"
#include "config.h"
#include "shell_cmds.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>

void shellInitialize(int argc, char *argv[], char *dir) {
    // the path of the games directory must be included
    if (argc != 2) {
        handleError(1);
    }

    // gets the game directory
    strcpy(dir, argv[1]);

    // exits program if directory is invalid
    if (!isDirectoryValid(dir)) {
        handleError(1);
    }
}

void shellLoop(char dir[PATH_MAX + 1]) {
    setjmp(errorJump); // if a non exiting error is found, code jumps to here
    
    while(true) {

        struct userInput* input = malloc(sizeof(struct userInput));
        getUserInput(input); // gets user input

        fflush(stdout); // flush to stdout after asking user for input
        
        // pointers here are used as simpler access to input
        char **cmds = input->commands;
        const int cmds_size = input->commands_size;
        const bool is_rdt = input->is_redirect;

        // exits the program is user types "exit"
        if (!strcmp(cmds[0], "exit")) {
            if (cmds_size != 1) {
                handleError(0); // if user types the exit command incorrectly, the program is not exited
            }
            exit(0);
        }

        else if (!strcmp(cmds[0], "path")) {
            // path command must have 1 argument
            if (cmds_size != 2 || is_rdt || !isDirectoryValid(cmds[1])) {
                handleError(0);
            }
            
            strncpy(dir, cmds[1], PATH_MAX); // replaces the current dir
        }

        // prints all files found within the dir with info about each one
        else if (!strcmp(cmds[0], "ls")) {
            lsCommand(dir);
        }

        else {
            // launches games
            if (isFileInDirectory(cmds[0], dir)) { // checks if the first argument is a valid game name
                launchGame(dir, cmds, is_rdt, input->redirect);
            } 

            // unknown arguments are invalid
            else {
                handleError(0);
            }
        }

        free(input);
    }
}

void shellStart(int argc, char *argv[]) {
    char dir[PATH_MAX + 1]; // current directory
    shellInitialize(argc, argv, dir);

    shellLoop(dir); // starts infinite loop
}