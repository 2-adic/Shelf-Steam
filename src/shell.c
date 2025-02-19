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

void shellInitialize(int argc, char *argv[], char dir[PATH_MAX + 1]) {
    // the path of the games directory must be included
    if (argc != 2) {
        handleError(1);
    }

    // gets the game directory
    strncpy(dir, argv[1], PATH_MAX);
}

void shellLoop(char dir[PATH_MAX + 1]) {
    setjmp(errorJump); // if a non exiting error is found, code jumps to here
    
    while(true) {

        struct userInput* input = malloc(sizeof(struct userInput));
        getUserInput(input); // gets user input

        // printInput(input); // DELETE LATER
        
        // pointers here are used as simpler access to input
        char **cmds = input->commands;
        const int cmds_size = input->commands_size;
        const bool is_rdt = input->is_redirect;

        // exits the program is user types "exit"
        if (!strcmp(cmds[0], "exit")) {
            exit(0);
        }

        else if (!strcmp(cmds[0], "path")) {
            // path command must have 1 argument
            if (cmds_size != 2 || is_rdt) {
                handleError(1);
            }
            
            strncpy(dir, cmds[1], PATH_MAX); // replaces the current dir
        }

        else if (!strcmp(cmds[0], "ls")) {
            char dir_new[PATH_MAX + 1] = "/src"; 
            strcatReplace(dir, dir_new);

            lsCommand(dir_new);
            
            printf("\nNEEDS TO BE IMPLEMENTED (needs to be able to do --help)\n");
        }

        else if (!strcmp(cmds[0], "test")) {
            printf("this is a test\n");
        }

        else {
            // checks if the first argument is a valid game name
            char dir_temp[PATH_MAX + 1] = "/bin/"; 
            strcatReplace(dir, dir_temp);
            if (isFileInDirectory(cmds[0], dir_temp)) {
                launchGame(dir, cmds, is_rdt, input->redirect);
            } 

            // unknown arguments are invalid and exit the program
            else {
                handleError(1);
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