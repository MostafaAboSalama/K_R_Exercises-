#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int base);
void reverse(char s[]);

int main(void)
{
    char s[35];   /* Enough for 32-bit binary + '-' + '\0' */

    struct {
        int number;
        int base;
    } tests[] = {
        {0, 2},
        {10, 2},
        {-10, 2},

        {10, 8},
        {-10, 8},

        {26, 16},
        {-26, 16},

        {35, 36},
        {36, 36},
        {123456, 16},

        {2147483647, 10},     /* INT_MAX (32-bit) */
        {-2147483648, 10},    /* INT_MIN (32-bit) */

        {-2147483648, 2},     /* INT_MIN in binary */
        {-2147483648, 16}     /* INT_MIN in hexadecimal */
    };

    int numTests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < numTests; i++) {
        itob(tests[i].number, s, tests[i].base);
        printf("%12d (base %2d) -> %s\n",
               tests[i].number, tests[i].base, s);
    }

    return 0;
}

/*
 * Convert integer n to its character representation in the given base.
 *
 * Supports bases from 2 to 36.
 * Handles INT_MIN correctly by never negating n.
 */
void itob(int n, char s[], int base)
{
    int i = 0;
    int sign = n;

    /* Reject unsupported bases. */
    if (base < 2 || base > 36) {
        strcpy(s, "Invalid base");
        return;
    }

    do {
        /* Extract the least significant digit. */
        int digit = n % base;

        /* Make the digit positive before converting it. */
        if (digit < 0)
            digit = -digit;

        /* Convert the digit to its character representation. */
        char c;
        if (digit < 10)
            c = digit + '0';
        else
            c = digit - 10 + 'A';

        s[i++] = c;

    } while ((n /= base) != 0);

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
