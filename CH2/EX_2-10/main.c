#include <stdio.h>

/*
 * Convert uppercase letter to lowercase using
 * the conditional operator.
 * Non-uppercase characters are unchanged.
 */
int lower(int c);

int main(void)
{
    printf("%c\n", lower('A'));  /* a */
    printf("%c\n", lower('Z'));  /* z */
    printf("%c\n", lower('m'));  /* m */

    return 0;
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z')
           ? c + ('a' - 'A')
           : c;
}
