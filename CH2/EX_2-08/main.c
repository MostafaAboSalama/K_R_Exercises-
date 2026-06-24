#include <stdio.h>
#include <stdlib.h>

/* EX 2-8
 * Rotate x to the right by n bit positions.
 */
unsigned int rightRot(unsigned int x, unsigned int n);

int main(void)
{
    unsigned int x = 178; /* 10110010 */

    printf("x before = %u\n", x);

    x = rightRot(x, 3);

    printf("x after  = %u\n", x);

    return 0;
}

unsigned int rightRot(unsigned int x, unsigned int n)
{
    /* Number of bits in an unsigned int */
    unsigned int bits = sizeof(unsigned int) * 8;

    /* Extract the rightmost n bits */
    unsigned int y = x & ~(~0 << n);

    /* Make them the upper n bits */
    y <<= (bits - n);

    /* Shift x right by n positions */
    x >>= n;

    /* Oring */
    x |= y;

    return x;
}
