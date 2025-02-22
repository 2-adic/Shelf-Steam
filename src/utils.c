#include "utils.h"
#include "shell_cmds.h"
#include "config.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

// prints user arguments for testing purposes
void printInput(struct userInput* input) {
    printf("\nCommands: %d\n", input->commands_size);
    for (int i = 0; i < input->commands_size; i++) {
        printf("%d: %s\n", i, input->commands[i]);
    }

    printf("\nRedirects: %d\n", input->is_redirect);
    printf("%s\n", input->redirect);
}

// checks if a string ends in the char '/'
bool isStringEndSlash(const char *str) {
    if (str == NULL || *str == '\0') {
        return false; // handles empty and NULL strings
    }
    
    size_t len = strlen(str);
    return str[len - 1] == '/';
}

// adds the '/' char to the end of a directory if a user doesn't add one
void correctDirectory(char *dir) {
    if (!isStringEndSlash(dir)) {
        strcat(dir, "/");
    }
}

// qsort comparison function
int compareEntries(const void *a, const void *b) {
    return strcmp((*(struct dirent **)a)->d_name, (*(struct dirent **)b)->d_name);
}

bool isFileInDirectory(const char *filename, const char *dirpath) {
    DIR *dir = opendir(dirpath);
    if (dir == NULL) {
        perror("opendir");
        return false; // directory could not be opened.
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // compare the current entry's name with the target filename.
        if (strcmp(entry->d_name, filename) == 0) {
            closedir(dir);
            return true;
        }
    }

    closedir(dir);
    return false;
}

void runProcess(char *dir, char **commands, bool is_redirect, const char *redirect, bool is_ls) {
    
    // creates full path for process
    char *dir_temp = malloc(strlen(dir) + strlen(commands[0]) + 1);
    strcpy(dir_temp, dir);

    correctDirectory(dir_temp); // adds '/' char to the end of the dir if needed

    strcat(dir_temp, commands[0]); // game full path

    pid_t pid = fork(); // creates new process that game will run on

    if (pid < 0) {
        handleError(1); // fork failure (exits out of child process)
    }

    if (pid == 0) { 

        // gets inputs for game replay feature
        if (is_redirect) {
            // open file in read mode
            int fd = open(redirect, O_RDONLY);
            if (fd < 0) {
                handleError(1); // failed to open replay file (exits out of child process)
            }
        
            // redirect standard input
            if (dup2(fd, STDIN_FILENO) < 0) {
                close(fd);
                handleError(1); // failed to redirect standard input (exits out of child process)
            }
        
            close(fd);
        }

        // runs the specified process
        execvp(dir_temp, commands);
        printf("(empty)\n");
        fflush(stdout);
        exit(1); // error if execvp fails (exits out of child process)
    } 
    
    // parent waits for child process to finish
    else { 
        int status;
        waitpid(pid, &status, 0);
    }

    free(dir_temp);
}

bool isAllWhitespace(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return 0; // non-whitespace char
        }

        str++;
    }

    return 1;
}

bool isDirectoryValid(const char *dir) {
    DIR *dir_ptr = opendir(dir);
    if (dir_ptr) {
        closedir(dir_ptr);
        return 1; // valid directory
    }

    return 0; // invalid directory
}