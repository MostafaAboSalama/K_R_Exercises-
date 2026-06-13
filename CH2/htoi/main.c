#include <stdio.h>
#include <stdlib.h>

int myatoi(char str[]);
int myhtoi(char str[]);

int main()
{
    char str[100];
    printf("Enter a string : ");
    gets(str);
    printf("%d\n", myatoi(str));

    return 0;
}

int myatoi(char str[])
{
    int i = 0, n = 0;
    while(str[i] != '\0')
    {
        n = (n * 10) + (str[i] - '0');
        i++;
    }
    return n;
}

int myhtoi(char str[])
{
    int i = 0, n = 0, digit;
    if((str[0] == '0' && (str[1] == 'x' || str[1] =='X'))) // skip 0x/0X at the beginning.
        i = 2;
    while(str[i] != '\0')
    {
        if(str[i] >= 'A' && str[i] <= 'F')
            digit = str[i] - 55;
        else if(str[i] >= 'a' && str[i] <= 'f')
            digit = str[i] - 87;
        else if(str[i] >= '0' && str[i] <= '9')
            digit = str[i] - '0';
        n = (n * 16) + digit;
        i++;
    }
    return n;
}
