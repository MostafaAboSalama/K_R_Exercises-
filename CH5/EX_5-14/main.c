#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES   100
#define MAXLEN     100

int getLine(char line[], int lim);
int readLines(char *lines[], int maxLines);
char *alloc(int len);
void writeLines(char *lines[], int nlines);

void my_qsort(void *v[], int left, int right, int (*comp)(void *, void *));
void reverseLines(void *v[], int n);
void swap(void *v[], int i, int j);
int numcmp(char *s1, char *s2);


int main(int argc, char *argv[])
{
    int nlines;
    char *lines[MAXLINES];
    int numeric = 0;
    int reverse = 0;

    /* Parse command-line options. */
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
            numeric = 1;          /* Numeric comparison */
        else if (strcmp(argv[i], "-r") == 0)
            reverse = 1;          /* Reverse output order */
        else
        {
            printf("Unknown option %s\n", argv[i]);
            return 1;
        }
    }

    /* Select the appropriate comparison function. */
    int (*fptr)(void *, void *) = (numeric ? numcmp : strcmp);

    /* Read, sort, optionally reverse, then print the lines. */
    if ((nlines = readLines(lines, MAXLINES)) >= 0)
    {
        my_qsort((void **)lines, 0, nlines - 1, fptr);

        if (reverse)
            reverseLines((void **)lines, nlines);

        writeLines(lines, nlines);
    }
    else
        printf("Input too big\n");

    return 0;
}


/*
 * Sort an array of pointers using quicksort.
 * The comparison function determines the ordering.
 */
void my_qsort(void *v[], int left, int right,
              int (*comp)(void *, void *))
{
    if (left >= right)
        return;

    /* Choose the middle element as the pivot. */
    int pivot = left + (right - left) / 2;
    int last = left;

    /* Move the pivot to the beginning. */
    swap(v, left, pivot);

    /* Partition the array around the pivot. */
    for (int i = left + 1; i <= right; i++)
    {
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }

    /* Put the pivot into its final position. */
    swap(v, left, last);

    /* Recursively sort the two partitions. */
    my_qsort(v, left, last - 1, comp);
    my_qsort(v, last + 1, right, comp);
}


/*
 * Reverse the order of the array.
 * Used to implement the -r option.
 */
void reverseLines(void *v[], int n)
{
    int i;

    for (i = 0; i < n / 2; i++)
        swap(v, i, n - i - 1);
}


/* Exchange two elements in an array of pointers. */
void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


/*
 * Compare two strings numerically.
 * Returns:
 *   >0 if s1 > s2
 *   <0 if s1 < s2
 *    0 if equal
 */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 > v2)
        return 1;
    else if (v2 > v1)
        return -1;
    else
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
 * Read all input lines and store them in dynamically
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

        /* Remove the trailing newline. */
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


/*
 * Allocate len bytes from a fixed-size buffer.
 * Returns NULL if there is not enough space.
 */
char *alloc(int len)
{
    if (allocBuf + ALLOCSIZE - allocp >= len)
    {
        allocp += len;
        return allocp - len;
    }

    return NULL;
}


/*
 * Print all stored lines.
 */
void writeLines(char *lines[], int nlines)
{
    while (nlines--)
        printf("%s\n", *lines++);
}
