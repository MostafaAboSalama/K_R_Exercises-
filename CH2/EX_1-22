#include <stdio.h>

#define WIDTH           20      /* Maximum output line width */
#define MAX_LENGTH      100     /* Maximum input line length */

int getLine(char s[], int lim);
void fold();

int main()
{
    fold();
    return 0;
}

/* Read a line into s, return its length */
int getLine(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}

/*
 * Fold a long line into shorter lines.
 *
 * start = beginning of current segment
 *
 * Look ahead WIDTH characters
 * │
 * ├─ found a space?
 * │      ├─ break at the last space
 * │      ├─ print current segment
 * │      ├─ print '\n'
 * │      └─ start = lastSpace + 1
 * │
 * └─ no space?
 *        ├─ force break at WIDTH
 *        ├─ print WIDTH characters
 *        ├─ print '\n'
 *        └─ start += WIDTH
 *
 * Repeat until the entire line has been processed.
 */

void fold()
{
    int lastSpace = 0;      /* Position of last blank in current window */
    int pos = 0;            /* Current scanning position */
    int length = 0;         /* Length of input line */
    int start = 0;          /* Start of current output segment */
    int spaceFound = 0;     /* True if a blank was found in window */
    int end = WIDTH - 1;    /* End of current search window */

    char string[MAX_LENGTH];

    length = getLine(string, MAX_LENGTH);

    while (start < length)
    {
        /* Remaining text already fits on one line */
        if (length - start <= WIDTH)
        {
            for (int i = start; i < length; i++)
                printf("%c", string[i]);
            break;
        }

        /* Find the last blank in the current window */
        for (pos = start; pos <= end && pos < length; pos++)
        {
            if (string[pos] == ' ')
            {
                spaceFound = 1;
                lastSpace = pos;
            }
        }

        if (spaceFound)
        {
            /* Fold at the last blank found */
            for (int i = start; i < lastSpace; i++)
                printf("%c", string[i]);

            printf("\n");

            start = lastSpace + 1;
        }
        else
        {
            /* No blank found: force a break at WIDTH */
            for (int i = start; i <= end && i < length; i++)
                printf("%c", string[i]);

            printf("\n");

            start += WIDTH;
        }

        /* Prepare next search window */
        spaceFound = 0;
        end = start + WIDTH - 1;
    }
}
