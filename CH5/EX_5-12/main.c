#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100

int detab(char str[], int maxLen, int start, int step);
void entab(int start, int step);
int nextTabStop(int col, int start, int step);


int main(int argc, char *argv[])
{
    char line[MAX_LEN] = "";
    int len;

    /* Default tab settings. */
    int start = 0;
    int step = 8;

    /*
     * Usage:
     *   ./prog            -> start = 0, step = 8
     *   ./prog 4          -> start = 0, step = 4
     *   ./prog -5 +4      -> start = 5, step = 4
     */
    if (argc == 2)
    {
        step = atoi(argv[1]);
    }
    else if (argc == 3)
    {
        start = atoi(argv[1] + 1);   /* Skip '-' */
        step  = atoi(argv[2] + 1);   /* Skip '+' */
    }

    /* entab(start, step); */

    while ((len = detab(line, MAX_LEN, start, step)) > 0)
    {
        if (line[0] != '\0')
            printf("%s", line);
    }

    return 0;
}

/* Replace tabs in the input line with the proper number
 * of spaces to reach the next tab stop.
 */
int detab(char str[], int maxLen, int start, int step)
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
                /* Expand a tab to the next tab stop. */
				spaceNum = nextTabStop(column, start, step) - column;
				
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
void entab(int start, int step)
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
			int next = nextTabStop(col, start, step);
			
			while (col + spaceNum >= next)
			{
			    putchar('\t');
			
			    while (col < next)
			    {
			        col++;
			        spaceNum--;
			    }
			
			    next = nextTabStop(col, start, step);
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

/* Return the next tab stop after the current column. */
int nextTabStop(int col, int start, int step)
{
    if (col < start)
        return start;

    return start + (((col - start) / step) + 1) * step;
}
