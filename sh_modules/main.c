#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "command_utils.h"
#include "custom_string.h"
#include <string.h>

#define MAX_ARGS 10 /* Maximum number of arguments for the command */

extern char** environ;

int compareStrings(const char *str1, const char *str2)
{
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

size_t calculateLength(const char *str)
{
    size_t length = 0;
    while (*str) {
        length++;
        str++;
    }
    return length;
}


int command_exists(const char* command) {
    /* Resolve the command path */
    char* command_path = resolve_command_path(command);
    if (command_path == NULL) {
        return 0; /* Command not found */
    }

    /* Free the allocated memory */
    free(command_path);

    return 1; /* Command exists */
}

int path_exists(const char* path) {
    if (access(path, F_OK) != -1) {
        return 1; /* Path exists */
    } else {
        return 0; /* Path does not exist */
    }
}



int main()
{

    char *input = NULL;
    size_t bufsize = 0;
    ssize_t characters;
    char *command;
    char *command_path;
    pid_t pid;
    char *args[MAX_ARGS + 2]; /* Array to hold the command and its arguments */
    int status;
/* ssize_t input_length; */
int i = 0;

    while (1) {
        /* Display prompt */
        write(STDOUT_FILENO, ":) ", 3);

        /* Read user input */
        characters = getline(&input, &bufsize, stdin);


        /* Check for end of file (Ctrl+D) */
        if (characters == -1) {
            if (input)
                free(input);
            break;
        }

        /* Remove newline character at the end, if present */
        if (input[characters - 1] == '\n') {
            input[characters - 1] = '\0';
        }

        /* Check if input is empty */
        if (is_empty_input(input)) {
            continue;
        }

        /* Check if the command is "exit" */
        if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input[3] == 't' && input[4] == '\0') {
            /* Exit the shell */
            break;
        }





        /* Check if the input matches the "env" command */
        if (compareStrings(input, "env") == 0) {
            /* Print environment variables */
            for (i = 0; environ[i] != NULL; i++) {
                write(STDOUT_FILENO, environ[i], calculateLength(environ[i]));
                write(STDOUT_FILENO, "\n", 1);
            }
            continue; /* Continue to the next iteration of the loop */
        }

        /* Parse the input into a command and its arguments */

       /* int i = 0; */
        i = 0;
	args[i] = strtok(input, " \t");

        /* Split the input string by spaces and tabs */
        while (args[i] != NULL && i < MAX_ARGS) {
            args[++i] = strtok(NULL, " \t");
        }

        /* Set the last argument to NULL */
        args[i] = NULL;



/* Check if the absolute path exists */
        if (args[0][0] == '/' && !path_exists(args[0])) {
        perror("Absolute path");
            continue;
        }

        /* Check and execute if the command is an absolute path */
       /* char *command = args[0]; */

command = args[0];
if (command[0] == '/') {
            /* Fork a child process */
            pid_t child_pid = fork();
            if (child_pid == -1) {
                perror("fork");
                return 1;
            } else if (child_pid == 0) {
                /* Child process */
                execve(command, args, NULL);
                /* If execve returns, an error occurred */
                perror("Absolute path");
                continue;
            } else {
                /* Parent process */
                waitpid(child_pid, &status, 0);
            }
            continue;
        }


	/* Check if the command exists */
        if (!command_exists(args[0])) {
            perror("Command");
            continue;
        }


        /* Resolve the command path */
       /* char *command_path = resolve_command_path(command); */
command_path = resolve_command_path(command);
        if (command_path == NULL) {
            perror("Command");
            continue;
        }

        /* Execute the command */
        /* pid_t pid = fork(); */
	pid = fork();
        if (pid == -1) {
            perror("fork");
            free(command_path);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */
            execve(command_path, args, NULL);
            /* execve only returns if an error occurs */
             perror("execve");
                free(command_path);
            exit(EXIT_FAILURE);
        } else {
            /* Parent process */
            wait(&status);
            free(command_path);
        }
    }
    free(input);
    return 0;
}
