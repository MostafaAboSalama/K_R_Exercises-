#include <stdio.h>
#include <stdlib.h>

/*Find the first position in s1 that contains any character that appears in s2.*/

int any(char s1[], char s2[]);

int main()
{
    char s1[] = "hello";
    char s2[] = "xyzl";
    printf("%d", any(s1, s2));
    return 0;
}

int any(char s1[], char s2[])
{
    int i = 0, j = 0;
    for(i = 0; s1[i] != '\0'; i++)
    {
        for(j = 0; s2[j] != '\0'; j++)
        {
            if(s1[i] == s2[j])
            {
                return i;
            }
        }
    }
    return -1;
}
