#include <stdio.h>

/*
 * swap(t, x, y)
 *
 * Generic macro to swap two variables of the same type.
 *
 * Parameters:
 *   t - data type of x and y
 *   x - first variable
 *   y - second variable
 */
#define swap(t, x, y) { \
    t temp;             \
    temp = x;           \
    x = y;              \
    y = temp;           \
}

int main(void)
{
    /* Test 1: int */
    int a = 10;
    int b = 20;

    printf("Before swap (int): a = %d, b = %d\n", a, b);

    swap(int, a, b);

    printf("After  swap (int): a = %d, b = %d\n\n", a, b);

    /* Test 2: char */
    char c1 = 'A';
    char c2 = 'Z';

    printf("Before swap (char): c1 = %c, c2 = %c\n", c1, c2);

    swap(char, c1, c2);

    printf("After  swap (char): c1 = %c, c2 = %c\n\n", c1, c2);

    /* Test 3: double */
    double x = 3.14;
    double y = 2.71;

    printf("Before swap (double): x = %.2f, y = %.2f\n", x, y);

    swap(double, x, y);

    printf("After  swap (double): x = %.2f, y = %.2f\n\n", x, y);

    /* Test 4: pointers */
    char *p = "Hello";
    char *q = "World";

    printf("Before swap (pointer): p = %s, q = %s\n", p, q);

    swap(char *, p, q);

    printf("After  swap (pointer): p = %s, q = %s\n", p, q);

    return 0;
}
