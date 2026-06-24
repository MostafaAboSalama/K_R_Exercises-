#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getLine(char s[], int lim);
int strrindex(char s[], char t[]);

int main(void)
{
    char s[MAXLINE];
    char t[MAXLINE];
    int pos;

    printf("Enter the main string: ");
    getLine(s, MAXLINE);

    printf("Enter the substring to search for: ");
    getLine(t, MAXLINE);


    pos = strrindex(s, t);

    if (pos >= 0)
        printf("Rightmost occurrence found at index %d\n", pos);
    else
        printf("Substring not found\n");

    return 0;
}

/*
 * Read a line into s, return its length.
 */
int getLine(char s[], int lim)
{
    int c, i = 0;

    while ((c = getchar()) != EOF &&
           c != '\n' &&
           i < lim - 1)
    {
        s[i++] = c;
    }

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}

/*
 * Return the position of the rightmost occurrence
 * of t in s, or -1 if there is no match.
 */
int strrindex(char s[], char t[])
{
    int i, j, k;
    int slen = strlen(s);
    int tlen = strlen(t);

    /* Start from the end of s */
    for (i = slen - 1; i >= 0; i--)
    {
        /*
         * Compare backwards:
         * s[j] with t[k]
         */
        for (j = i, k = tlen - 1;
             k >= 0 && j >= 0 && s[j] == t[k];
             j--, k--)
        {
            ;   /* do nothing */
        }

        /*
         * If k became -1, all characters
         * of t matched successfully.
         */
        if (k < 0)
            return j + 1;
    }

    return -1;
}
