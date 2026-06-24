#include <stdio.h>

int myhtoi(char str[]);

int main(void)
{
    char str[100];

    printf("Enter a hexadecimal number: ");
    fgets(str, sizeof(str), stdin);

    printf("Decimal value = %d\n", myhtoi(str));

    return 0;
}

/* Convert a hexadecimal string to its decimal value */
int myhtoi(char str[])
{
    int i = 0;
    int n = 0;
    int digit;

    /* Skip optional 0x or 0X prefix */
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        i = 2;

    while (str[i] != '\0' && str[i] != '\n')
    {
        if (str[i] >= '0' && str[i] <= '9')
            digit = str[i] - '0';
        else if (str[i] >= 'A' && str[i] <= 'F')
            digit = str[i] - 'A' + 10;
        else if (str[i] >= 'a' && str[i] <= 'f')
            digit = str[i] - 'a' + 10;
        else
            break;      /* Invalid hexadecimal digit */

        n = 16 * n + digit;
        i++;
    }

    return n;
}
