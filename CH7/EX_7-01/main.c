#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int my_strlen(char *str);
int my_strcmp(const char *s1, const char *s2);

int main(int argc, char *argv[])
{
    int len = my_strlen(argv[0]);
    int c, i;
    char *name = NULL;

    /* Find the last '/' in the program name */
    for(i = len - 1; i >= 0; i--)
	{
		if(argv[0][i] == '/')
		{	
			break;
		}
	}
	
	name = argv[0] + i + 1;

    /* Select the conversion based on the executable name */
    if (my_strcmp(name, "lower") == 0)
    {
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    }
    else if (my_strcmp(name, "upper") == 0)
    {
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    }
    else
    {
        printf("Invalid program name\n");
    }
    
    return 0;
}

int my_strlen(char *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;

    return len;
}

int my_strcmp(const char *s1, const char *s2)
{
    /* Advance while characters match */
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    /* Return 0 if equal, <0 if s1<s2, >0 if s1>s2 */
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

