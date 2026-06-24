#include <stdio.h>
#include <limits.h>

int main(void)
{
    /* Maximum unsigned values: all bits set to 1 */
    unsigned char  uchar_max  = (unsigned char)~0;
    unsigned short ushort_max = (unsigned short)~0;
    unsigned int   uint_max   = (unsigned int)~0;
    unsigned long  ulong_max  = (unsigned long)~0;

    /*
     * For two's complement systems:
     * INT_MAX is obtained by shifting UINT_MAX right by one bit.
     * INT_MIN = -INT_MAX - 1
     */

    signed char  schar_max = (signed char)(uchar_max >> 1);
    signed char  schar_min = -schar_max - 1;

    short shrt_max = (short)(ushort_max >> 1);
    short shrt_min = -shrt_max - 1;

    int int_max = (int)(uint_max >> 1);
    int int_min = -int_max - 1;

    long long_max = (long)(ulong_max >> 1);
    long long_min = -long_max - 1;

    printf("=== Values from limits.h ===\n\n");

    printf("signed char  : %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char: 0 to %u\n\n", UCHAR_MAX);

    printf("short         : %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: 0 to %u\n\n", USHRT_MAX);

    printf("int          : %d to %d\n", INT_MIN, INT_MAX);
    printf("unsigned int : 0 to %u\n\n", UINT_MAX);

    printf("long         : %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long: 0 to %lu\n\n", ULONG_MAX);

    printf("=== Computed Values ===\n\n");

    printf("signed char  : %d to %d\n", schar_min, schar_max);
    printf("unsigned char: 0 to %u\n\n", uchar_max);

    printf("short         : %d to %d\n", shrt_min, shrt_max);
    printf("unsigned short: 0 to %u\n\n", ushort_max);

    printf("int          : %d to %d\n", int_min, int_max);
    printf("unsigned int : 0 to %u\n\n", uint_max);

    printf("long         : %ld to %ld\n", long_min, long_max);
    printf("unsigned long: 0 to %lu\n", ulong_max);

    return 0;
}
