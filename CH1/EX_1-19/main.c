/*
 * Exercise 1-19 (K&R)
 * Reverse each input line.
 */

#include <stdio.h>

#define MAX_LINE 100

int getLine(char line[], int lim);
void reverse(char line[]);

int main(void)
{
    int len;
    char line[MAX_LINE];

    /* Process each line independently */
    while ((len = getLine(line, MAX_LINE)) > 0)
    {
        reverse(line);
        printf("%s", line);
    }

    return 0;
}

/*
 * Read a line and return its length
 */
int getLine(char line[], int lim)
{
    int c, i;
    int len = 0;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        line[i] = c;
        len++;
    }

    if (c == '\n')
    {
        line[i++] = c;
        len++;
    }

    line[i] = '\0';
    return len;
}

/*
 * Reverse a string in place
 */
void reverse(char line[])
{
    int i = 0, j;
    char temp;

    /* find end of string */
    while (line[i] != '\0')
        i++;

    i--;

    /* ignore newline if present */
    if (i >= 0 && line[i] == '\n')
        i--;

    /* swap characters */
    for (j = 0; j <= i / 2; j++)
    {
        temp = line[j];
        line[j] = line[i - j];
        line[i - j] = temp;
    }
}
