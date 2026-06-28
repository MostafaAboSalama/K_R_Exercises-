#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main(void)
{
    char s[20];

    int tests[] = {
        0,
        7,
        -7,
        123456,
        -123456,
        2147483647,    // INT_MAX (32-bit)
        -2147483648    // INT_MIN (32-bit)
    };

    int numTests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < numTests; i++) {
        itoa(tests[i], s);
        printf("%12d -> %s\n", tests[i], s);
    }

    return 0;
}

/*
 * Convert integer n to its character representation in s.
 *
 * Unlike the old version, this implementation never negates n,
 * so it correctly handles INT_MIN, whose positive value cannot
 * be represented by an int.
 */
void itoa(int n, char s[])
{
    int i = 0;
    int sign = n;

    do {
        /* Extract the last digit. */
        int digit = n % 10;

        /* Make the digit positive before converting to a character. */
        if (digit < 0)
            digit = -digit;

        s[i++] = digit + '0';

    } while ((n /= 10) != 0);

    /* Add the minus sign if the original number was negative. */
    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';

    reverse(s);
}

/* Reverse a null-terminated string in place. */
void reverse(char s[])
{
    int len = strlen(s);

    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = temp;
    }
}
