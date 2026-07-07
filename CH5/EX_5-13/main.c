#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES   100
#define MAXLEN     100

int getLine(char line[], int lim);
int readLines(char *lines[], int maxLines);
char *alloc(int len);
void writeLines(char *lines[], int nlines, int n);
int isNumber(char *s);

int main(int argc, char *argv[])
{
    int n = 10;                  /* Default: print last 10 lines */
    int nlines;
    char *lines[MAXLINES];

    /* Parse optional command-line argument (-n). */
    if (argc > 1)
    {
        if (argc == 2 && argv[1][0] == '-' && isNumber(argv[1] + 1))
            n = atoi(argv[1] + 1);
        else
        {
            fprintf(stderr, "Usage: tail [-n]\n");
            return 1;
        }
    }

    /* Read all input lines. */
    if ((nlines = readLines(lines, MAXLINES)) >= 0)
        writeLines(lines, nlines, n);
    else
        printf("Input too big\n");

    return 0;
}

/*
 * Read a line and return its length.
 */
int getLine(char line[], int lim)
{
    int c, i;
    int len = 0;

    for (i = 0; i < lim - 1 &&
                (c = getchar()) != EOF &&
                c != '\n'; i++)
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
 * Read all lines from input and store them in dynamically
 * allocated memory obtained from alloc().
 */
int readLines(char *lines[], int maxLines)
{
    int len, nlines = 0;
    char *p;
    char line[MAXLEN];

    while ((len = getLine(line, MAXLEN)) > 0)
    {
        if (nlines >= maxLines || (p = alloc(len)) == NULL)
            return -1;

        /* Remove the newline if one was stored. */
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        strcpy(p, line);
        lines[nlines++] = p;
    }

    return nlines;
}

/* Simple allocator. */

#define ALLOCSIZE 10000

char allocBuf[ALLOCSIZE];
char *allocp = allocBuf;

char *alloc(int len)
{
    /* Enough space remaining? */
    if (allocBuf + ALLOCSIZE - allocp >= len)
    {
        allocp += len;
        return allocp - len;
    }

    return NULL;
}

/*
 * Print the last n lines.
 */
void writeLines(char *lines[], int nlines, int n)
{
    int start = (n >= nlines) ? 0 : nlines - n;

    for (int i = start; i < nlines; i++)
        printf("%s\n", lines[i]);
}

/*
 * Return 1 if the string contains only digits,
 * otherwise return 0.
 */
int isNumber(char *s)
{
    if (*s == '\0')
        return 0;

    while (*s)
    {
        if (!isdigit((unsigned char)*s))
            return 0;
        s++;
    }

    return 1;
}
