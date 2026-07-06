#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100

int detab(char str[], int maxLen, int tabstop);
void entab(int tabstop);

int main(int argc, char* argv[])
{
    char line[MAX_LEN] = "";
    int len = 0;
    int tabstop = 8;          /* default */

	if (argc > 1)
	    tabstop = atoi(argv[1]);
	
	entab(tabstop);           
	
	/* Read lines, replacing tabs with spaces */
    /*while ((len = detab(line, MAX_LEN, tabstop)) > 0)
    {
        if (line[0] != '\0')
            printf("%s", line);
    }*/
    return 0;
}

/* Replace tabs in the input line with the proper number
 * of spaces to reach the next tab stop.
 */
int detab(char str[], int maxLen, int tabstop)
{
    int c;
    int pos = 0;      /* position in output buffer */
    int len = 0;      /* total characters processed */
    int column = 0;   /* current column position */
    int spaceNum = 0; /* spaces needed for a tab */

    while ((c = getchar()) != EOF && c != '\n')
    {
        if (pos < maxLen - 1)
        {
            if (c != '\t')
            {
                str[pos++] = c;
                len++;
                column++;
            }
            else
            {
                /* Move to the next tab stop */
                spaceNum = tabstop - (column % tabstop);

                for (int i = 0; i < spaceNum; i++)
                {
                    if (pos < maxLen - 1)
                    {
                        str[pos++] = ' ';
                        len++;
                        column++;
                    }
                }
            }
        }
    }

    /* Preserve newline if present */
    if (c == '\n')
    {
        if (pos < maxLen - 1)
            str[pos++] = c;

        len++;
    }

    /* Terminate the string */
    str[pos] = '\0';

    return len;
}


/* Replace strings of blanks with the minimum number of tabs and spaces. */
void entab(int tabstop)
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
            while (col / tabstop != (col + spaceNum) / tabstop)
            {
                /* A tab moves to the next tab stop. */
                putchar('\t');

                /* Advance to the next tab stop. */
                do
                {
                    col++;
                    spaceNum--;
                }
                while (col % tabstop != 0);
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
