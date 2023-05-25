#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "command_utils.h"
#include "custom_string.h"
#include <string.h>

/**
 * compareStrings - Compare two strings and return the result.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: The result of the string comparison.
 */

int compareStrings(const char *str1, const char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
return (*str1 - *str2);

str1++;
str2++;
}
return (*str1 - *str2);
}

/**
 * calculateLength - Calculate the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */

size_t calculateLength(const char *str)
{
size_t length = 0;
while (*str)
{
length++;
str++;
}
return (length);
}

/**
 * command_exists - Check if a command exists.
 * @command: The command to check.
 *
 * Return: 1 if the command exists, 0 otherwise.
 */

int command_exists(const char *command)
{
/* Resolve the command path */
char *command_path = resolve_command_path(command);
if (command_path == NULL)
return (0); /* Command not found */

/* Free the allocated memory */
free(command_path);
return (1); /* Command exists */
}

/**
 * path_exists - Check if a path exists.
 * @path: The path to check.
 *
 * Return: 1 if the path exists, 0 otherwise.
 */

int path_exists(const char *path)
{
if (access(path, F_OK) != -1)
return (1); /* Path exists */
else
return (0); /* Path does not exist */
}
