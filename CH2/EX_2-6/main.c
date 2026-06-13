#include <stdio.h>
#include <stdlib.h>

unsigned int setbits(unsigned int x, unsigned int pos, unsigned int n, unsigned int y);

int main(void)
{
    unsigned int x = 255;  /* 11111111 */
    unsigned int y = 2;    /* 00000010 */

    printf("x before = %u\n", x);
    printf("y        = %u\n", y);

    x = setbits(x, 4, 3, y);

    printf("x after  = %u\n", x);

    return 0;
}

unsigned int setbits(unsigned int x, unsigned int pos, unsigned int n, unsigned int y)
{
    /* Clear the target field in x */
    x &= ~(~(~0 << n) << (pos - n + 1));

    /* Extract the rightmost n bits from y */
    y &= ~(~0 << n);

    /* Move them into the target position */
    y <<= (pos - n + 1);

    /* Insert the bits into x */
    x |= y;

    return x;
}
