/*
 * Exercise 1-12
 * Print input one word per line.
 */

#include <stdio.h>

int main(void)
{
    int c;
    int inWord = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            if (inWord)
            {
                putchar('\n');
                inWord = 0;
            }
        }
        else
        {
            putchar(c);
            inWord = 1;
        }
    }

    return 0;
}
