#include <stdio.h>
#include <stdlib.h>

/* EX 2-7
 * Invert (toggle) the n bits ending at position pos.
 */
unsigned int invert(unsigned int x, unsigned int pos, unsigned int n);

int main(void)
{
    unsigned int x = 255; /* 11111111 */

    printf("x before = %u\n", x);

    x = invert(x, 4, 3);

    printf("x after  = %u\n", x);

    return 0;
}

unsigned int invert(unsigned int x, unsigned int pos, unsigned int n)
{

    x ^= (~(~0 << n)) << (pos - n + 1);

    return x;
}
