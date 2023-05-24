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
 * search_command_path - Search for the full path of a command.
 * @command: The command to resolve.
 * @path: The path
 * Return: A pointer to the resolved command path on success
 * or NULL on failure.
 */
char *search_command_path(const char *command, const char *path);

/**
 * custom_getenv - Retrieves the value of the specified environment variable.
 *
 * @name: The name of the environment variable.
 * Return: The value of the environment variable if found, NULL otherwise.
 */
char *custom_getenv(const char *name);

/**
 * create_command_path - Full path of a command.
 * @command: The command to resolve.
 * @directory: The directory
 *
 * Return: A pointer to the resolved command path on success
 * or NULL on failure.
 **/
char *create_command_path(const char *directory, const char *command);

/**
 * build_command_path - Build the command path by
 * concatenating directory and command.
 * @directory: The directory to concatenate.
 * @command: The command to concatenate.
 *
 * Return: A pointer to the concatenated command path on success
 * or NULL on failure.
 **/
char *build_command_path(const char *directory, const char *command);

#endif /* COMMAND_UTILS_H */
