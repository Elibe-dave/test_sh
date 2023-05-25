#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "command_utils.h"
#include "custom_string.h"
#include <string.h>

#define MAX_ARGS 10 /* Maximum number of arguments for the command */
/**
 * display_prompt_read_input - Display prompt and read user input.
 * @input: Pointer to the input string.
 * @bufsize: Pointer to the size of the buffer.
 *
 * This function displays the prompt ":)" and
 * reads the user input from stdin
 * into the buffer pointed by @input with the size @bufsize.
 * It checks for the end of file (Ctrl+D) and
 * handles freeing the input buffer
 * in case of an error or end of file.
 */
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

/**
 * print_environment_variables - Print environment variables.
 *
 * This function prints the environment variables
 * to the standard output.
 * It retrieves the environment variables from
 * the `environ` array.
 */
void print_environment_variables(void)
{
int i;
/* Print environment variables */
for (i = 0; environ[i] != NULL; i++)
{
write(STDOUT_FILENO, environ[i], calculateLength(environ[i]));
write(STDOUT_FILENO, "\n", 1);
}
}
