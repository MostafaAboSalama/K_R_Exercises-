/*
 * Exercise 1-16
 * Print the longest input line.
 * (K&R version with basic buffer handling)
 */

#include <stdio.h>

#define MAX_LINE 100

int getLine(char string[], int lim);
void copy(char to[], char from[]);

int main(void)
{
    int len = 0;     /* current line length */
    int max = 0;     /* maximum length seen so far */

    char line[MAX_LINE];
    char longest[MAX_LINE] = "";

    /* Read lines one by one */
    while ((len = getLine(line, MAX_LINE)) > 0)
    {
        /* Update longest line */
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }

    /* Print the longest line found */
    if (max > 0)
        printf("%s", longest);

    return 0;
}

/*
 * Read a line into 'string' up to lim-1 characters.
 * Returns full length of the line (even if truncated).
 */
int getLine(char string[], int lim)
{
    int c;
    int pos = 0;
    int len = 0;

    while ((c = getchar()) != EOF && c != '\n')
    {
        if (pos < lim - 1)
            string[pos++] = c;

        len++;
    }

    if (c == '\n')
    {
        if (pos < lim - 1)
            string[pos++] = c;

        len++;
    }

    string[pos] = '\0';
    return len;
}

/*
 * Copy string from 'from' to 'to'
 */
void copy(char to[], char from[])
{
    int i = 0;

    while ((to[i] = from[i]) != '\0')
        i++;
}
