#ifndef COMMAND_UTILS_H
#define COMMAND_UTILS_H

extern char **environ; /* Access the environment variables */

/**
 * is_empty_input - Check if the input string is empty.
 * @input: The input string.
 *
 * Return: 1 if the input is empty, 0 otherwise.
 */
int is_empty_input(const char *input);

/**
 * resolve_command_path - Resolve the full path of a command.
 * @command: The command to resolve.
 *
 * Return: A pointer to the resolved command path on success
 * or NULL on failure.
 */
char *resolve_command_path(const char *command);

/**
 * custom_getenv - Retrieves the value of the specified environment variable.
 *
 * @name: The name of the environment variable.
 * Return: The value of the environment variable if found, NULL otherwise.
 */
char *custom_getenv(const char *name);

#endif /* COMMAND_UTILS_H */
