#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100
#define TAB_STOP 4

int detab(char str[], int maxLen);

int main(void)
{
    char line[MAX_LEN] = "";
    int len = 0;

    /* Read lines, replacing tabs with spaces */
    while ((len = detab(line, MAX_LEN)) > 0)
    {
        if (line[0] != '\0')
            printf("%s", line);
    }

    return 0;
}

/* Replace tabs in the input line with the proper number
 * of spaces to reach the next tab stop.
 */
int detab(char str[], int maxLen)
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
                spaceNum = TAB_STOP - (column % TAB_STOP);

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
