#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "command_utils.h"
#include "custom_string.h"
#include <string.h>

#define MAX_ARGS 10 /* Maximum number of arguments for the command */

/**
 * main - Entry point of the program.
 *
 * This function serves as the entry point of the program.
 * It executes the main logic of the program, such as handling
 * user input, calling other functions, and producing the desired output.
 *
 * Return: The exit status of the program.
 */

int main(void)
{

char *input = NULL;
size_t bufsize = 0;
char *command;
char *command_path;
pid_t pid;
char *args[MAX_ARGS + 2]; /* Array to hold the command and its arguments */
int status;
int i = 0;

while (1)
{
display_prompt_read_input(&input, &bufsize);

if (is_empty_input(input))
continue;
if (input[0] == 'e' && input[1] == 'x' &&
input[2] == 'i' && input[3] == 't' &&
input[4] == '\0')
break;

if (compareStrings(input, "env") == 0)
{
print_environment_variables();
continue;
}
i = 0;
args[i] = strtok(input, " \t");

while (args[i] != NULL && i < MAX_ARGS)
args[++i] = strtok(NULL, " \t");

args[i] = NULL;
if (args[0][0] == '/' && !path_exists(args[0]))
{
perror("Absolute path");
continue;
}
command = args[0];
if (command[0] == '/')
{
pid_t child_pid = fork();
if (child_pid == -1)
{
perror("fork");
return (1);
}
else if (child_pid == 0)
{
execve(command, args, NULL);
perror("Absolute path");
continue;
}
else
{
waitpid(child_pid, &status, 0);
}
continue;
}
if (!command_exists(args[0]))
{
perror("Command");
continue;
}
command_path = resolve_command_path(command);
if (command_path == NULL)
{
perror("Command");
continue;
}
pid = fork();
if (pid == -1)
{
perror("fork");
free(command_path);
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execve(command_path, args, NULL);
perror("execve");
free(command_path);
exit(EXIT_FAILURE);
}
else
{
wait(&status);
free(command_path);
}
}
free(input);
return (0);
}
