#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int minWidth);
void reverse(char s[]);

int main(void)
{
    char s[40];   /* Large enough for padding and 32-bit integers */

    struct {
        int number;
        int width;
    } tests[] = {
        {0, 1},
        {0, 5},

        {7, 1},
        {7, 5},

        {-7, 5},

        {123, 3},
        {123, 6},

        {-123, 4},
        {-123, 7},

        {123456, 10},
        {-123456, 10},

        {2147483647, 15},      /* INT_MAX (32-bit) */
        {-2147483648, 15}      /* INT_MIN (32-bit) */
    };

    int numTests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < numTests; i++) {
        itoa(tests[i].number, s, tests[i].width);

        printf("width=%2d | %12d -> \"%s\"\n",
               tests[i].width,
               tests[i].number,
               s);
    }

    return 0;
}

/*
 * Convert integer n to its character representation.
 * If the resulting string is shorter than minWidth,
 * pad it with leading spaces.
 *
 * Handles INT_MIN correctly by never negating n.
 */
void itoa(int n, char s[], int minWidth)
{
    int i = 0;
    int sign = n;

    do {
        /* Extract the least significant digit. */
        int digit = n % 10;

        /* Make the digit positive before converting it. */
        if (digit < 0)
            digit = -digit;

        s[i++] = digit + '0';

    } while ((n /= 10) != 0);

    /* Append the minus sign if the original number was negative. */
    if (sign < 0)
        s[i++] = '-';

    /* Append spaces so they become leading spaces after reversing. */
    while (i < minWidth)
        s[i++] = ' ';

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
