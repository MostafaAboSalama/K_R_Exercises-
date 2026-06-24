#include <stdio.h>

/*
 * my_strcat()
 * Appends the string src to the end of dest.
 *
 * Assumption:
 * - dest has enough space to hold the resulting string.
 */
void my_strcat(char *dest, char *src);

int main(void)
{
    char dest[100] = "Hello";
    char src[] = " World!";

    printf("Before concatenation:\n");
    printf("dest = \"%s\"\n", dest);
    printf("src  = \"%s\"\n\n", src);

    my_strcat(dest, src);

    printf("After concatenation:\n");
    printf("dest = \"%s\"\n", dest);

    return 0;
}

void my_strcat(char *dest, char *src)
{
    /* Move dest to the terminating '\0' character. */
    while (*dest)
        dest++;

    /*
     * Copy src to dest, including the terminating '\0'.
     *
     * The assignment expression:
     *     *dest++ = *src++
     *
     * 1. Copies the current character from src to dest.
     * 2. Advances both pointers.
     * 3. Returns the copied character as the value of the expression.
     *
     * The loop stops when '\0' is copied because '\0' evaluates to 0.
     */
    while ((*dest++ = *src++))
        ;
}
