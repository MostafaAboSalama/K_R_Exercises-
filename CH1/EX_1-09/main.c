/*
 * Exercise 1-9
 * Copy input to output, replacing each string of one
 * or more blanks by a single blank.
 */

#include <stdio.h>

int main(void)
{
    int c;
    int inSpace = 0;  /* True if the previous character was a space */

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            /* Print only the first space in a sequence */
            if (!inSpace)
            {
                putchar(' ');
                inSpace = 1;
            }
        }
        else
        {
            /* Print non-space characters and leave space sequence */
            putchar(c);
            inSpace = 0;
        }
    }

    return 0;
}
