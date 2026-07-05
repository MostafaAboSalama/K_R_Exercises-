#include <stdio.h>
#include <string.h>

#define MAXLINES    5000    /* maximum number of lines to be sorted */
#define MAXLEN      1000    /* maximum length of any input line */
#define MAXSTORAGE 100000   /* storage for all input lines */

char *lineptr[MAXLINES];    /* pointers to text lines */

/* Read input lines into storage[] and store pointers in lineptr[] */
int readlines(char *lineptr[], int maxlines, char storage[]);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int getLine(char string[], int lim);
void swap(char* v[], int i, int j);

int main(void)
{
    int nlines;
    char storage[MAXSTORAGE];

    if ((nlines = readlines(lineptr, MAXLINES, storage)) >= 0)
    {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("error: input too big to sort\n");
        return 1;
    }
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

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char storage[])
{
    int len;
    int nlines = 0;
    int storageIndex = 0;

    char line[MAXLEN];
    char *p;

    while ((len = getLine(line, MAXLEN)) > 0)
    {
        /* Check for too many lines or insufficient storage space */
        if (nlines >= maxlines || storageIndex + len > MAXSTORAGE)
            return -1;

        /* Remove the trailing newline */
        line[len - 1] = '\0';

        /* Point to the next free location in storage */
        p = storage + storageIndex;

        /* Copy the line into the supplied storage buffer */
        strcpy(p, line);

        /* Save a pointer to the beginning of this line */
        lineptr[nlines++] = p;

        /* Advance to the next free position */
        storageIndex += len;
    }

    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;

    void swap(char *v[], int i, int j);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);

    last = left;

    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);

    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap : interchang v[i], v[j] */
void swap(char* v[], int i, int j)
{
	char* temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
