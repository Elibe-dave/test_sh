#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "command_utils.h"
#include "custom_string.h"
#include <string.h>

#define MAX_ARGS 10 /* Maximum number of arguments for the command */
#define MAX_FILENAME_LENGTH 256 /* Example value, adjust according to your needs */

/**
* main - Entry point of the program
* @argc: The number of command-line arguments
* @argv: An array of strings containing the arguments
*
* Return: Always 0 (indicating successful execution)
*/

/**
 * int main(int argc, char *argv[])
 * {
 * if (argc == 2)
 * {
 **/
int main(int argc, char *argv[])
/* int main(void) */
{
if (argc == 2)
/* Running in non-interactive mode */
/*run_non_interactive_mode(argv[1]);*/
{
perror("non");
run_non_interactive_mode(argv[1]);
return (0);
exit(0);
}
return(0);
}
