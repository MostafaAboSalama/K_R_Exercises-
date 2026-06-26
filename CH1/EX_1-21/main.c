#include <stdio.h>

#define TAB_STOP 8

void entab(void);

int main(void)
{
    entab();
    return 0;
}

/* Replace strings of blanks with the minimum number of tabs and spaces. */
void entab(void)
{
    int c;
    int col = 0;       /* Current output column. */
    int spaceNum = 0;  /* Number of consecutive buffered spaces. */

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            /* Buffer spaces until a non-space character is found. */
            spaceNum++;
        }
        else
        {
            /* Output buffered spaces using as many tabs as possible. */
            while (col / TAB_STOP != (col + spaceNum) / TAB_STOP)
            {
                /* A tab moves to the next tab stop. */
                putchar('\t');

                /* Advance to the next tab stop. */
                do
                {
                    col++;
                    spaceNum--;
                }
                while (col % TAB_STOP != 0);
            }

            /* Output any remaining spaces. */
            while (spaceNum > 0)
            {
                putchar(' ');
                col++;
                spaceNum--;
            }

            /* Output the current non-space character. */
            putchar(c);

            if (c == '\n')
                col = 0;      /* Start a new line. */
            else
                col++;
        }
    }

    /* Flush trailing spaces if the input ends with spaces. */
    while (spaceNum > 0)
    {
        putchar(' ');
        spaceNum--;
    }
}
