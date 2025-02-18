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
    while(1) {

        struct userInput* input = malloc(sizeof(struct userInput));
        getUserInput(input); // gets user input

        printInput(input); // DELETE LATER
        
        // pointers here are used as simpler access to input
        const char (*cmds)[MAX_CMD_LENGTH + 1] = input->commands;
        const int cmds_size = input->commands_size;
        const char (*rdt)[MAX_CMD_LENGTH + 1] = input->std_redirect;
        const int rdt_size = input->std_redirect_size;

        // exits the program is user types "exit"
        if (!strcmp(cmds[0], "exit")) {
            exit(0);
        }

        else if (!strcmp(cmds[0], "path")) {
            // path command must have 1 argument
            if (cmds_size != 2 || rdt_size != 0) {
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

        // command: game_name arguments...
        else if (!strcmp(cmds[0], "test1")) {
            char dir_new[PATH_MAX + 1] = "/bin/"; 
            strcatReplace(dir, dir_new); 
            strcat(dir_new, cmds[0]); // adds the game name to the end of the list

            printf("%s", dir_new);
            
            // char *args[] = {dir_new, "argument1", NULL};
            // execvp(dir_new, args);
            // perror("execvp failed");
        }

        else if (!strcmp(cmds[0], "test")) {
            printf("\nthis is a test\n");
        }

        else {
            
        }

        free(input);
    }
}

void shellStart(int argc, char *argv[]) {
    char dir[PATH_MAX + 1]; // current directory
    shellInitialize(argc, argv, dir);

    shellLoop(dir); // starts infinite loop
}