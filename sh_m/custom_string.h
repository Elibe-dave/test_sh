#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * custom_strlen - Calculate the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
size_t custom_strlen(const char *str);

/**
 * custom_strcmp - Compare two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: An integer less than, equal to
 * or greater than zero if str1 is found,
 * respectively, to be less than, to match, or be greater than str2.
 */
int custom_strcmp(const char *str1, const char *str2);

/**
 * custom_strdup - Duplicate a string.
 * @str: The input string.
 *
 * Return: A pointer to the newly allocated duplicate string.
 */
char *custom_strdup(const char *str);

/**
 * custom_strcat - Concatenate two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: A pointer to the newly allocated string
 * containing the concatenated strings.
 */
char *custom_strcat(const char *str1, const char *str2);

/**
 * custom_strncmp - Compare at most n characters of two strings
 * @str1: The first string to compare
 * @str2: The second string to compare
 * @n: The maximum number of characters to compare
 *
 * Return: 0 if the strings are equal, a negative value if str1 is less than
 * str2, or a positive value if str1 is greater than str2
 */
int custom_strncmp(const char *str1, const char *str2, size_t n);

void execute_interactive_mode(void);


void run_non_interactive_mode(const char *filename);

int execute_command(char *command, char **args);

#endif /* CUSTOM_STRING_H */
