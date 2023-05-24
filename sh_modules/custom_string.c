#include <stdlib.h>
#include "custom_string.h"

size_t custom_strlen(const char *str)
{
    const char *p = str;
    while (*p != '\0') {
        p++;
    }
    return p - str;
}

int custom_strcmp(const char *str1, const char *str2)
{
    while (*str1 == *str2) {
        if (*str1 == '\0') {
            return 0;  /* Strings are equal */
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

char *custom_strdup(const char *str) {
    size_t len = 0;
    char *new_str;
    size_t i = 0;

    while (str[len] != '\0') {
        len++;
    }

    new_str = malloc((len + 1) * sizeof(char));
    if (new_str == NULL) {
        perror("malloc");
        return NULL;
    }

    for (i = 0; i <= len; i++) {
        new_str[i] = str[i];
    }

    return new_str;
}


char *custom_strcat(const char *str1, const char *str2)
{
    size_t len1 = 0;
    size_t len2 = 0;
    char *new_str;
    size_t i;
    size_t j;

    while (str1[len1] != '\0') {
        len1++;
    }

    while (str2[len2] != '\0') {
        len2++;
    }

    new_str = malloc(len1 + len2 + 1);
    if (new_str == NULL) {
        perror("malloc");
        return NULL;
    }

    i = 0;
    for (; i < len1; i++) {
        new_str[i] = str1[i];
    }

    j = 0;
    for (; j <= len2; j++) {
        new_str[i + j] = str2[j];
    }

    return new_str;
}


int custom_strncmp(const char *str1, const char *str2, size_t n)
{
    if (n == 0)
        return 0;

    while (*str1 && (*str1 == *str2) && --n) {
        ++str1;
        ++str2;
    }

    return *(unsigned char *)str1 - *(unsigned char *)str2;
}
