#include <stdio.h>
#include <stdlib.h>

/* Delete each character in s1 that matches any character in the string s2.*/

void squeeze(char s1[], char s2[]);

int main()
{
    char s1[] = "abcdefg";
    char s2[] = "bdf";
    squeeze(s1, s2);
    printf("%s", s1);
    return 0;
}

void squeeze(char s1[], char s2[])
{
    int i = 0, j = 0, k = 0, found = 0;
    for(i = 0; s1[i] != '\0'; i++)
    {
        found = 0;
        for(j = 0; s2[j] != '\0'; j++)
        {
            if(s1[i] == s2[j])
            {
                found = 1;
                break;
            }
        }
        if(!found)
            s1[k++] = s1[i];
    }
    s1[k] = '\0';
}
