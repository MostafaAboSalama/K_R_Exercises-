/*
 * Exercise 1-10
 * Copy input to output, replacing tabs, backspaces,
 * and backslashes with their visible escape sequences.
 */

#include <stdio.h>

int main(void)
{
    int c;

    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
            printf("\\t");      /* Tab -> \t */

        else if (c == '\b')
            printf("\\b");      /* Backspace -> \b */

        else if (c == '\\')
            printf("\\\\");     /* Backslash -> \\ */

        else
            putchar(c);         /* Print all other characters unchanged */
    }

    return 0;
}
