#include <stdio.h>

void itoa(int n, char s[]);
void itoa_r(int n, char s[], int *i);

int main(void)
{
    char s[20];

    itoa(12345, s);
    printf("12345  -> %s\n", s);

    itoa(-9876, s);
    printf("-9876  -> %s\n", s);

    itoa(0, s);
    printf("0      -> %s\n", s);

    return 0;
}

/*
 * Public function.
 * Initializes the index and handles the sign.
 */
void itoa(int n, char s[])
{
    int i = 0;

    if (n < 0)
    {
        s[i++] = '-';
        n = -n;      /* Does not handle INT_MIN */
    }

    itoa_r(n, s, &i);

    s[i] = '\0';
}

/*
 * Recursive helper.
 * Stores digits from left to right as recursion unwinds.
 */
void itoa_r(int n, char s[], int *i)
{
    if (n / 10)
        itoa_r(n / 10, s, i);

    s[(*i)++] = n % 10 + '0';
}
