#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "command_utils.h"
#include "custom_string.h"
#include <string.h>

#define MAX_ARGS 10 /* Maximum number of arguments for the command */

/**
 * execute_command - Execute a specific command.
 * @command: The command to execute.
 * @args: An array of strings containing the arguments
 *
 * Description: This function executes a specific command
 * and performs the necessary actions based on the command
 * Return: Return value of the executed command
 **/

int execute_command(char *command, char **args)
{
pid_t pid;
int status;
char *command_path;

if (command[0] == '/')
{
pid = fork();
if (pid == -1)
{
perror("fork");
return (1);
}
else if (pid == 0)
{
execve(command, args, NULL);
perror("Absolute path");
exit(EXIT_FAILURE);
}
else
{
waitpid(pid, &status, 0);
}
}
else
{
if (!command_exists(command))
{
perror("Command");
return (1);
}
command_path = resolve_command_path(command);
if (command_path == NULL)
{
perror("Command");
return (1);
}
pid = fork();
if (pid == -1)
{
perror("fork");
free(command_path);
return (1);
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

return (0);
}

/**
 * run_non_interactive_mode - Execute the program in non-interactive mode.
 * @filename: The name of the file to process
 *
 * Description: This function handles the execution of the program
 * in non-interactive mode based on the provided argument.
 **/

void run_non_interactive_mode(const char *filename)
{
char *line;
size_t len;
ssize_t read;
FILE *file;
char *command;
char *args[MAX_ARGS + 1];
int arg_count;
int status;

file = fopen(filename, "r");
if (file == NULL)
perror("fopen");
return;

line = NULL;
len = 0;


while ((read = getline(&line, &len, file)) != -1)
{
/* Remove the trailing newline character, if any */
if (line[read - 1] == '\n')
line[read - 1] = '\0';

/* Tokenize the line into command and arguments */
command = strtok(line, " \t");
/* args[MAX_ARGS + 1]; */
arg_count = 0;

while (command != NULL && arg_count < MAX_ARGS)
{
args[arg_count++] = command;
command = strtok(NULL, " \t");
}
args[arg_count] = NULL;

/* Execute the command */
status = execute_command(args[0], args);

if (status != 0)
{
perror("Command");
free(command);
exit(EXIT_FAILURE);

/* You can choose to break here or continue with the remaining commands */
}
}

free(line);
fclose(file);
}

/**
 * execute_interactive_mode - Execute the program in interactive mode.
 *
 * Description: This function handles the execution of the program
 * in interactive mode, allowing user interaction and input.
 **/

void execute_interactive_mode(void)
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
display_prompt();
read_input(&input, &bufsize);
/* Rest of your original code goes here... */

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
return;
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

/* free(input); */
}
