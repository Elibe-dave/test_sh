#include "custom_string.h"
#include "command_utils.h"

/**
 * Retrieves the value of the specified environment variable.
 *
 * @param name The name of the environment variable.
 * @return The value of the environment variable if found, NULL otherwise.
 */
char *custom_getenv(const char *name)
{
size_t name_len;
int i;
char *current_env;
extern char **environ; /* Access the environment variables */

    if (name == NULL || environ == NULL)
        return NULL;

    name_len = custom_strlen(name);

    for (i = 0; environ[i] != NULL; i++)
    {
        current_env = environ[i];

        if (custom_strncmp(current_env, name, name_len) == 0 && current_env[name_len] == '=')
        {
            /* Found the matching environment variable */
            return &current_env[name_len + 1];
        }
    }

    return NULL; /* Environment variable not found*/

}
