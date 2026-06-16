/*
 * Exercise 1-17 (K&R)
 * Print all input lines longer than 80 characters.
 *
 * Key idea:
 * We must count the FULL line length even if we store
 * only part of it in a fixed buffer.
 */

#include <stdio.h>

#define MAX_LINE 100
#define MIN_LEN  80

int getLine(char line[], int lim);

int main(void)
{
    int len;                  /* full length of current line */
    char line[MAX_LINE];      /* buffer (may truncate long lines) */

    /* Read lines one by one */
    while ((len = getLine(line, MAX_LINE)) > 0)
    {
        /* Print only long lines */
        if (len > MIN_LEN)
            printf("%s", line);
    }

    return 0;
}

/*
 * getLine:
 * - Reads a line from input
 * - Stores up to lim-1 characters
 * - Always returns FULL length of the line (not truncated length)
 */
int getLine(char line[], int lim)
{
    int c;
    int i = 0;
    int len = 0;

    /* Read characters until newline or EOF */
    while ((c = getchar()) != EOF && c != '\n')
    {
        /* Store only if space is available */
        if (i < lim - 1)
            line[i++] = c;

        len++;  /* always count full input length */
    }

    /* Include newline if present */
    if (c == '\n')
    {
        if (i < lim - 1)
            line[i++] = c;

        len++;
    }

    /* Null terminate the stored string */
    line[i] = '\0';

    return len;
}
