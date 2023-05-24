#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "custom_string.h"
#include "command_utils.h"


int is_empty_input(const char *input)
{
    while (*input != '\0') {
        if (*input != ' ' && *input != '\t') {
            return 0; /* Not empty */
        }
        input++;
    }
    return 1; /* Empty */
}

char *resolve_command_path(const char *command)
{
/*    char *path = getenv("PATH"); */
char *path = custom_getenv("PATH");
    char *path_copy;
    char *token;
    char *command_path;
char *temp_path;

  
   if (path == NULL) {
   perror("getenv");
   return NULL;
   }
 

path_copy = custom_strdup(path);
    if (path_copy == NULL) {
        return NULL;
    }

   token = strtok(path_copy, ":");
    while (token != NULL) {
  command_path = custom_strcat(token, "/");
        if (command_path == NULL) {
            free(path_copy);
            return NULL;
        }
      temp_path = custom_strcat(command_path, command);
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
