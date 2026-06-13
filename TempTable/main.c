#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 20

/*int getline(char string[], int max);
void reverseCopy(char from[], char to[]);
void trim(char string[], int len);
void reverseCopyV2(char str[]);*/

int main()
{

   printf("hello, " "world");
   /* char line[MAX_LEN] = "", revLine[MAX_LEN] = "";
    int len = 0;
    while((len = getline(line, MAX_LEN)) > 0)
    {
        reverseCopyV2(line);
        if(line[0] != '\0')
            printf("%s\n", line);
    }*/

    return 0;
}

/*int getline(char string[], int max)
{
    int c;
    int pos = 0, len = 0;
    while(((c = getchar()) != EOF) && c != '\n')
    {
        if( pos < max - 1)
            string[pos++] = c;
        len++;
    }

    if(c == '\n')
    {
        if( pos < max - 1)
            string[pos++] = c;
        len++;
    }

    string[pos] = '\0';
    return len;
}

void trim(char string[], int len)
{
    int i = 0;
    while(string[i] != '\0')
        i++;

    i--;
    if(i >= 0 && string[i] == '\n')
        i--;
    while(i >= 0 && (string[i] == ' ' || string[i] == '\t'))
        i--;

    string[i+1] = '\0';
    printf("size = %d\n", i+1);
}
void reverseCopy(char from[], char to[])
{
    int i = 0, j = 0;
    while(from[i] != '\0')
        i++;
    i--;
    if(i >= 0 && from[i] == '\n')
        i--;
    while(i >= 0)
    {
        to[j] = from[i];
        i--;
        j++;
    }

    to[j] = '\0';
}

void reverseCopyV2(char str[])
{
    int i = 0, j;
    char temp;

    while(str[i] != '\0')
        i++;

    i--;

    if(i >= 0 && str[i] == '\n')
        i--;

    for(j = 0; j < (i + 1) / 2; j++)
    {
        temp = str[j];
        str[j] = str[i - j];
        str[i - j] = temp;
    }
}
*/
