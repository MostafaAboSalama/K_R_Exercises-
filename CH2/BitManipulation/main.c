#include <stdio.h>
#include <stdlib.h>


                        /* DRAFT */

/* BIT_MATHS AS MACROS */
#define GET_BIT(NUM,BIT_NUM)    (((NUM) >> (BIT_NUM)) & 1)
#define SET_BIT(NUM,BIT_NUM)    ((NUM) |= (1 << (BIT_NUM)))
#define CLEAR_BIT(NUM,BIT_NUM)  ((NUM) &= ~(1 << (BIT_NUM)))
#define TOG_BIT(NUM,BIT_NUM)    ((NUM) ^= (1 << (BIT_NUM)))

/* BIT_MATHS AS FUNCTIONS */
unsigned int getBit(unsigned int num, unsigned int bitNum);
unsigned int setBit(unsigned int num, unsigned int bitNum);
unsigned int clearBit(unsigned int num, unsigned int bitNum);
unsigned int toggleBit(unsigned int num, unsigned int bitNum);
unsigned int getBits(unsigned int num, unsigned int pos, unsigned int n);
unsigned int setBits(unsigned int num, unsigned int pos, unsigned int n);


/* BOOK EXERCISES */

/* EX 2-6 */
unsigned int setbits(unsigned int x, unsigned int pos, unsigned int n, unsigned int y);
/* EX 2-7 */
unsigned int invert(unsigned int x, unsigned int pos, unsigned int n);
/* EX 2-8 */
unsigned int rightRot(unsigned int x, unsigned int n);

int main()
{
    //unsigned int num = 10; /* 1010 */

    //printf("Initial value: %u\n\n", num);

    /* Function Tests */
    /*printf("=== Function Tests ===\n");
    printf("getBit(10,1) = %u\n", getBit(num, 1));
    printf("setBit(10,0) = %u\n", setBit(num, 0));
    printf("clearBit(10,1) = %u\n", clearBit(num, 1));
    printf("toggleBit(10,3) = %u\n\n", toggleBit(num, 3));*/

    /* Macro Tests */
   /* printf("=== Macro Tests ===\n");

    num = 10;
    printf("num = %u\n", num);

    printf("GET_BIT(num,1) = %u\n", GET_BIT(num, 1));

    SET_BIT(num, 0);
    printf("After SET_BIT(num,0): %u\n", num);

    CLEAR_BIT(num, 1);
    printf("After CLEAR_BIT(num,1): %u\n", num);

    TOG_BIT(num, 3);
    printf("After TOG_BIT(num,3): %u\n", num);
    */

    //unsigned int num = 182;  /* 10110110 */

   /* printf("num = %u\n", num);

    printf("getBits(num, 4, 3) = %u\n", getBits(num, 4, 3));
    printf("getBits(num, 7, 4) = %u\n", getBits(num, 7, 4));
    printf("getBits(num, 2, 2) = %u\n", getBits(num, 2, 2));*/

   /* printf("%u\n", setBits(0, 4, 3));     // 28
    printf("%u\n", setBits(0, 7, 4));     // 240
    printf("%u\n", setBits(10, 4, 3));  */  // 30

   // printf("%u\n", setbits(255, 4, 3, 2));
  // printf("%u\n", invert(255, 4, 3));
  //unsigned int x = 178; /* 10110010 */

    /*printf("Original:\n");
    printf("Decimal: %u\n", x);

    printf("\nRotate right by 3:\n");

    unsigned int result = rightRot(x, 3);

    printf("Decimal: %u\n", result);*/
    return 0;
}

unsigned int getBit(unsigned int num, unsigned int bitNum)
{
    return (num >> bitNum) & 1;
}

unsigned int setBit(unsigned int num, unsigned int bitNum)
{
    num |= (1 << bitNum);
    return num;
}
unsigned int clearBit(unsigned int num, unsigned int bitNum)
{
    num &= ~(1 << bitNum);
    return num;
}
unsigned int toggleBit(unsigned int num, unsigned int bitNum)
{
    num ^= (1 << bitNum);
    return num;
}

unsigned int getBits(unsigned int num, unsigned int pos, unsigned int n)
{
    return (num >> (pos - n + 1) & ~(~0 << n));
}

unsigned int setBits(unsigned int num, unsigned int pos, unsigned int n)
{
    num |= (~(~0 << n) << (pos - n + 1));
    return num;
}
unsigned int clearBits(unsigned int num, unsigned int pos, unsigned int n)
{
    num &= ~((~(~0 << n) << (pos - n + 1)));
    return num;
}


unsigned int setbits(unsigned int x, unsigned int pos, unsigned int n, unsigned int y)
{
    /* clear those bits in x*/
    x &= ~((~(~0 << n) << (pos - n + 1)));

    y = y & (~(~0 << n));
    y = y << pos - n + 1;

    x |= y;

    return x;
}

unsigned int invert(unsigned int x, unsigned int pos, unsigned int n)
{
    x ^= ((~(~0 << n)) << (pos - n + 1));
    return x;
}
unsigned int rightRot(unsigned int x, unsigned int n)
{
    /* word size */
    unsigned int bits = sizeof(unsigned int) * 8;
    /* get those bits from x*/
    unsigned int y = (x & ~(~0 << n));
    /* making them the upper n bits */
    y = y << (bits - n);
    /* right shift x by n */
    x = x >> n;
    /* Oring*/
    x |= y;

    return x;
}
