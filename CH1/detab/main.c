#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100
#define TAB_STOP    4

int detab(char str[], int maxLen);

int main()
{
    char line[MAX_LEN] = "";
    int len = 0;
    while((len = detab(line, MAX_LEN)) > 0)
    {
        if(line[0] != '\0')
            printf("%s\n", line);
    }
    return 0;
}

int detab(char str[], int maxLen)
{
    int c, pos = 0, len = 0, spaceNum = 0, column = 0;
    while((c = getchar()) != EOF && c !='\n')
    {
        if(pos < maxLen -1)
        {
            if(c != '\t')
            {
                str[pos++] = c;
                len++;
                column++;
            }
            else
            {
                spaceNum = TAB_STOP - (column % TAB_STOP);
                for(int i = 0; i < spaceNum; i++)
                {
                    if(pos < maxLen -1)
                    {
                        str[pos++] = ' ';
                        len++;
                        column++;
                    }
                }
            }
        }
    }
    if(c == '\n')
    {
        if( pos < maxLen - 1)
            str[pos++] = c;
        len++;
    }

    str[pos] = '\0';
    return len;
}
