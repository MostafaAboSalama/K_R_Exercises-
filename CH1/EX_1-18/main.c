/*
 * Exercise 1-18 (K&R)
 * Remove trailing blanks and tabs from each input line
 * and skip empty lines.
 */

#include <stdio.h>

#define MAX_LINE 100

int getLine(char string[], int lim);
void trim(char string[], int len);

int main(void)
{
    int len;
    char line[MAX_LINE];

    while ((len = getLine(line, MAX_LINE)) > 0)
    {
        /* Remove trailing whitespace */
        trim(line, len);

        /* Print only non-empty lines */
        if (line[0] != '\0')
            printf("%s\n", line);
    }

    return 0;
}

/*
 * getLine:
 * Reads a line, stores up to lim-1 chars,
 * returns FULL length (not truncated length).
 */
int getLine(char string[], int lim)
{
    int c;
    int i = 0;
    int len = 0;

    while ((c = getchar()) != EOF && c != '\n')
    {
        if (i < lim - 1)
            string[i++] = c;

        len++;
    }

    if (c == '\n')
    {
        if (i < lim - 1)
            string[i++] = c;

        len++;
    }

    string[i] = '\0';
    return len;
}

/*
 * trim:
 * Removes trailing spaces and tabs.
 * Also removes newline if present.
 */
void trim(char string[], int len)
{
    int i = len - 1;

    /* Remove newline */
    if (i >= 0 && string[i] == '\n')
    {
        string[i] = '\0';
        i--;
    }

    /* Remove trailing blanks and tabs */
    while (i >= 0 && (string[i] == ' ' || string[i] == '\t'))
    {
        string[i] = '\0';
        i--;
    }
}
