#include <stdio.h>

char* my_strncpy(char *dest, const char *src, int n);
char* my_strncat(char *dest, const char *src, int n);
int my_strncmp(const char *str1, const char *str2, int n);

int main(void)
{
    char dest1[20];
    char dest2[50] = "Hello ";

    printf("=== my_strncpy() ===\n");

    my_strncpy(dest1, "Hi", 5);

    /*
     * Since strncpy() may not append a '\0',
     * print the first 5 characters manually.
     */
    for (int i = 0; i < 5; i++)
    {
        if (dest1[i] == '\0')
            printf("\\0 ");
        else
            printf("%c ", dest1[i]);
    }
    printf("\n\n");

    printf("=== my_strncat() ===\n");

    my_strncat(dest2, "World", 3);

    printf("Result: %s\n\n", dest2);

    printf("=== my_strncmp() ===\n");

    printf("my_strncmp(\"hello\", \"help\", 3) = %d\n",
           my_strncmp("hello", "help", 3));

    printf("my_strncmp(\"hello\", \"help\", 4) = %d\n",
           my_strncmp("hello", "help", 4));

    printf("my_strncmp(\"abc\", \"abc\", 10) = %d\n",
           my_strncmp("abc", "abc", 10));

    return 0;
}

/*
 * Copy at most n characters from src to dest.
 *
 * If src is shorter than n, pad the remaining
 * characters with '\0'.
 *
 * Behaves like the standard strncpy().
 */
char* my_strncpy(char *dest, const char *src, int n)
{
    char *dest_temp = dest;
    const char *src_temp = src;

    while (n--)
    {
        if (*src_temp)
            *dest_temp++ = *src_temp++;
        else
            *dest_temp++ = '\0';
    }

    return dest;
}

/*
 * Append at most n characters from src
 * to the end of dest.
 *
 * Always appends a terminating '\0'.
 *
 * Behaves like the standard strncat().
 */
char* my_strncat(char *dest, const char *src, int n)
{
    char *dest_temp = dest;
    const char *src_temp = src;

    /* Move to the end of dest. */
    while (*dest_temp)
        dest_temp++;

    /* Copy at most n characters from src. */
    while (n-- && *src_temp)
        *dest_temp++ = *src_temp++;

    /* Terminate the resulting string. */
    *dest_temp = '\0';

    return dest;
}

/*
 * Compare at most n characters of str1 and str2.
 *
 * Returns:
 *   < 0 if str1 < str2
 *   = 0 if str1 == str2
 *   > 0 if str1 > str2
 *
 * Behaves like the standard strncmp().
 */
int my_strncmp(const char *str1, const char *str2, int n)
{
    while (n--)
    {
        if (*str1 != *str2)
            return *str1 - *str2;

        if (*str1 == '\0')
            return 0;

        str1++;
        str2++;
    }

    return 0;
}
