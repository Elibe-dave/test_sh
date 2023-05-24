#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "custom_string.h"
#include "command_utils.h"

/**
* is_empty_input - Check if the input string is empty.
* @input: The input string.
*
* Return: 1 if the input is empty, 0 otherwise.
**/

int is_empty_input(const char *input)
{
while (*input != '\0')
{
if (*input != ' ' && *input != '\t')
{
return (0); /* Not empty */
}
input++;
}
return (1); /* Empty */
}

/**
* resolve_command_path - Resolve the full path of a command.
* @command: The command to resolve.
*
* Return: A pointer to the resolved command path on success
* or NULL on failure.
**/

char *resolve_command_path(const char *command)
{
/*    char *path = getenv("PATH"); */
char *path = custom_getenv("PATH");
char *path_copy = custom_strdup(path);
char *token = strtok(path_copy, ":");
char *resolved_path = NULL;

if (path == NULL)
{
perror("getenv");
return (NULL);
}
if (path_copy == NULL)
{
return (NULL);
}
while (token != NULL)
{
resolved_path = build_command_path(token, command);
if (resolved_path == NULL)
{
free(path_copy);
return (NULL);
}

if (access(resolved_path, X_OK) == 0)
{
free(path_copy);
return (resolved_path);
}

free(resolved_path);
token = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}

/**
* build_command_path - Build the command path by
* concatenating directory and command.
* @directory: The directory to concatenate.
* @command: The command to concatenate.
*
* Return: A pointer to the concatenated command path on success
* or NULL on failure.
**/
char *build_command_path(const char *directory, const char *command)
{
char *command_path;
char *temp_path;

command_path = custom_strcat(directory, "/");
if (command_path == NULL)
{
return (NULL);
}

temp_path = custom_strcat(command_path, command);
free(command_path);

return (temp_path);
}
