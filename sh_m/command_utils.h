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

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void);

/**
 * read_user_input - Read user input from stdin.
 * @input: Pointer to the input buffer.
 * @bufsize: Pointer to the buffer size.
 * Return: The number of characters read.
 */
ssize_t read_user_input(char **input, size_t *bufsize);

/**
 * is_exit_command - Check if the input is the "exit" command.
 * @input: The input string.
 * Return: 1 if the input is the "exit" command, 0 otherwise.
 */
int is_exit_command(const char *input);


/**
 * is_env_command - Check if the input is the "env" command.
 * @input: The input string.
 * Return: 1 if the input is the "env" command, 0 otherwise.
 */
int is_env_command(const char *input);


/**
 * print_environment_variables - Print environment variables.
 */
void print_environment_variables(void);


/**
 * parse_input - Parse the user input into command and arguments.
 * @input: The user input string.
 * @args: The array to hold the command and arguments.
 * Return: The number of arguments parsed.
 */
void parse_input(char *input, char *args[]);

/**
 * execute_command - Execute a command with given arguments.
 * @command: The command to execute.
 * @args: The array of arguments for the command.
 * Return: 0 on success, 1 on failure.
 */

/*void execute_command(const char *command, char *args[]); */
/* int execute_command(const char *command, char **args); */

/**
 * path_exists - Check if a path exists.
 * @path: The path to check.
 *
 * Return: 1 if the path exists, 0 otherwise.
 */

int path_exists(const char *path);

/**
 * command_exists - Check if a command exists.
 * @command: The command to check.
 *
 * Return: 1 if the command exists, 0 otherwise.
 */

int command_exists(const char *command);

/**
 * calculateLength - Calculate the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */

size_t calculateLength(const char *str);

/**
 * compareStrings - Compare two strings and return the result.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: The result of the string comparison.
 */

int compareStrings(const char *str1, const char *str2);


void read_input(char **input, size_t *bufsize);


void print_environment_variables(void);

void check_and_execute_absolute_path(char *command, char *args[]);

void display_prompt(void);


#endif /* COMMAND_UTILS_H */
