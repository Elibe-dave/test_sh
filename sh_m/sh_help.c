#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "command_utils.h"
#include "custom_string.h"
#include <string.h>

#define MAX_ARGS 10 /* Maximum number of arguments for the command */

void display_prompt_read_input(char **input, size_t *bufsize)
{
ssize_t characters;

/* Display prompt */
write(STDOUT_FILENO, ":) ", 3);

/* Read user input */
characters = getline(input, bufsize, stdin);

/* Check for end of file (Ctrl+D) */
if (characters == -1)
{
if (*input)
free(*input);
return;
}

/* Remove newline character at the end, if present */
if ((*input)[characters - 1] == '\n')
(*input)[characters - 1] = '\0';
}

void print_environment_variables()
{
int i;
/* Print environment variables */
for (i = 0; environ[i] != NULL; i++)
{
write(STDOUT_FILENO, environ[i], calculateLength(environ[i]));
write(STDOUT_FILENO, "\n", 1);
}
}
