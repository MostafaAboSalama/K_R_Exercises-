#include <stdio.h>


int bitcount(unsigned int x);

int main(void)
{
    int x;

    printf("Enter a number: ");
    scanf("%d", &x);

    printf("Number of ones = %d\n", bitcount(x));

    return 0;
}

/*
 * Each iteration removes the rightmost 1-bit.
 * Number of iterations = number of 1 bits.
 */
int bitcount(unsigned int x)
{
    int b = 0;

    while (x != 0)
    {
        x &= (x - 1);  /* drop lowest set bit */
        b++;
    }

    return b;
}
