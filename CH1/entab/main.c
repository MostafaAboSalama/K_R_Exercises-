#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100
#define TAB_STOP    4

int entab(char str[], int maxLen);

int main()
{
    char line[MAX_LEN] = "";
    int len = 0;
    while((len = entab(line, MAX_LEN)) > 0)
    {
        if(line[0] != '\0')
            printf("%s", line);
    }
    return 0;
}

int entab(char str[], int maxLen)
{
    int c, pos = 0, len = 0, spaceNum = 0, tabNum = 0, column = 0;
    while((c = getchar()) != EOF && c !='\n')
    {
        if(pos < maxLen -1)
        {
            if(str[pos] == ' ')
            {
                spaceNum++;
                if(spaceNum % TAB_STOP == 0)
                {
                    tabNum = TAB_STOP / spaceNum;
                    spaceNum = 0;
                    for(int i = 0; i < tabNum; i++)
                    {
                        str[pos++] = '\t';
                        len++;
                    }
                }
                else
                {
                    str[pos++] = c;
                    len++;
                }
            }
            else
            {
                spaceNum = 0;
                tabNum = 0;
                if( pos < maxLen - 1)
                    str[pos++] = c;
                len++;
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
