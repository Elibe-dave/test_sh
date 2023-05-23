#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 10 // Maximum number of arguments for the command

#define PATH_MAX_LEN 1024 // Maximum length of the PATH environment variable

size_t custom_strlen(const char* str) {
    const char* p = str;
    while (*p != '\0') {
        p++;
    }
    return p - str;
}

int custom_strcmp(const char* str1, const char* str2) {
    while (*str1 == *str2) {
        if (*str1 == '\0') {
            return 0;  // Strings are equal
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}


char* custom_strdup(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char* new_str = malloc(len + 1);
    if (new_str == NULL) {
        perror("malloc");
        return NULL;
    }

    for (size_t i = 0; i <= len; i++) {
        new_str[i] = str[i];
    }

    return new_str;
}


char* custom_strcat(const char* str1, const char* str2) {
    size_t len1 = 0;
    while (str1[len1] != '\0') {
        len1++;
    }

    size_t len2 = 0;
    while (str2[len2] != '\0') {
        len2++;
    }

    char* new_str = malloc(len1 + len2 + 1);
    if (new_str == NULL) {
        perror("malloc");
        return NULL;
    }

    size_t i = 0;
    for (; i < len1; i++) {
        new_str[i] = str1[i];
    }

    size_t j = 0;
    for (; j <= len2; j++) {
        new_str[i + j] = str2[j];
    }

    return new_str;
}



//char* custom_getenv(const char* var_name) {
//    extern char** environ;

//    size_t var_name_len = custom_strlen(var_name);
//    for (char** env = environ; *env != NULL; env++) {
//        if (custom_strcmp(*env, var_name) == 0 && (*env)[var_name_len] == '=') {
//            return &((*env)[var_name_len + 1]);
//        }
//    }

//    return NULL;  // Variable not found
//}

char* custom_getenv(const char* var_name) {
    extern char** environ;

    size_t var_name_len = 0;
    const char* p = var_name;
    while (*p != '\0') {
        var_name_len++;
        p++;
    }

    for (char** env = environ; *env != NULL; env++) {
        char* current_var = *env;

        // Compare variable name character by character
        size_t i;
        for (i = 0; i < var_name_len; i++) {
            if (current_var[i] != var_name[i]) {
                break;
            }
        }

        // Check for a match
        if (i == var_name_len && current_var[i] == '=') {
            return &(current_var[i + 1]); // Return value part of the environment variable
        }
    }

    return NULL; // Variable not found
}


 


char* resolve_command_path(const char* command) {
//char* path = getenv("PATH");
char* path = custom_getenv("PATH");
    	if (path == NULL) {
        fprintf(stderr, "Error: PATH environment variable not found.\n");
        return NULL;
    }

    char* path_copy = custom_strdup(path);
    if (path_copy == NULL) {
        return NULL;
    }

    char* token = strtok(path_copy, ":");
    while (token != NULL) {
        char* command_path = custom_strcat(token, "/");
        if (command_path == NULL) {
            free(path_copy);
            return NULL;
        }
        char* temp_path = custom_strcat(command_path, command);
        free(command_path);
        if (temp_path == NULL) {
            free(path_copy);
            return NULL;
        }

        if (access(temp_path, X_OK) == 0) {
            free(path_copy);
            return temp_path;
        }

        free(temp_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}


int compareStrings(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

size_t calculateLength(const char* str) {
    size_t length = 0;
    while (*str) {
        length++;
        str++;
    }
    return length;
}






int is_empty_input(const char *input) {
    while (*input != '\0') {
        if (*input != ' ' && *input != '\t') {
            return 0; // Not empty
        }
        input++;
    }
    return 1; // Empty
}





extern char** environ;

int main() {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t characters;
    char *args[MAX_ARGS + 2]; // Array to hold the command and its arguments
    int status;

    while (1) {
        // Display prompt
        write(STDOUT_FILENO, ":) ", 3);

        // Read user input
        characters = getline(&input, &bufsize, stdin);

        // Check for end of file (Ctrl+D)
        if (characters == -1) {
            if (input)
                free(input);
            break;
        }

        // Remove newline character at the end, if present
        if (input[characters - 1] == '\n') {
            input[characters - 1] = '\0';
        }

        // Check if input is empty
        if (is_empty_input(input)) {
            continue;
        }

// Check if the command is "exit" using custom_strcmp
//        if (custom_strcmp(input, "exit") == 0) {
//            break; // Exit the shell loop
//        }


// Check if the command is "exit"
    if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input[3] == 't' && input[4] == '\0') {
        // Exit the shell
        break;
    }



// Check if the input matches the "env" command
if (compareStrings(input, "env") == 0) {
    // Print environment variables
    for (int i = 0; environ[i] != NULL; i++) {
        write(STDOUT_FILENO, environ[i], calculateLength(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
    }
    continue; // Continue to the next iteration of the loop
}



        // Parse the input into a command and its arguments
        int i = 0;
        args[i] = strtok(input, " \t");

        // Split the input string by spaces and tabs
        while (args[i] != NULL && i < MAX_ARGS) {
            args[++i] = strtok(NULL, " \t");
        }

        // Set the last argument to NULL
        args[i] = NULL;

        // Execute the command
//        pid_t pid = fork();
//        if (pid == -1) {
//            perror("fork");
//            exit(EXIT_FAILURE);
//        } else if (pid == 0) {
            // Child process
//            execve(args[0], args, NULL);
//            // execve only returns if an error occurs
//            perror("execve");
//            exit(EXIT_FAILURE);
//        } else {
            // Parent process
//            wait(&status);
//        }
//
//
//
// Check and execute if the command is an absolute path
char* command = args[0];
    	if (command[0] == '/') {
        // Fork a child process
        pid_t child_pid = fork();
        if (child_pid == -1) {
            perror("fork");
            return 1;
        } else if (child_pid == 0) {
            // Child process
            execve(command, args, NULL);
            // If execve returns, an error occurred
            perror("Absolute path");
 //           exit(1);
 continue;
 	} else {
            // Parent process
            waitpid(child_pid, &status, 0);
        }
continue;
    }




// Resolve the command path
//        char* command = args[0];
        char* command_path = resolve_command_path(command);
        if (command_path == NULL) {
//            fprintf(stderr, "Error: Command '%s' not found.\n", command);
perror("Command");
continue;
        }
    
// Execute the command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            free(command_path);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execve(command_path, args, NULL);
            // execve only returns if an error occurs
            perror("execve");
            free(command_path);
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(&status);
            free(command_path);
        }
    }

    return 0;
}
