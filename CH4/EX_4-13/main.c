#include <stdio.h>
#include <string.h>

/* Function prototypes */
void reverse(char s[]);
void reverse_r(char s[], int left_pos, int right_pos);

int main(void)
{
    char s[] = "Mostafa AboSalama";

    reverse(s);

    printf("Reversed string: %s\n", s);

    return 0;
}

/*
 * reverse:
 * Initializes the left and right indices
 * and starts the recursive reversal.
 */
void reverse(char s[])
{
    reverse_r(s, 0, strlen(s) - 1);
}

/*
 * reverse_r:
 * Recursively swaps characters from the
 * outside toward the center.
 *
 * Example:
 * "Hello"
 *
 * H e l l o
 * ^       ^
 *
 * Swap H and o:
 * o e l l H
 *
 * Then recurse on:
 * e l l
 */
void reverse_r(char s[], int left_pos, int right_pos)
{
    char temp;

    /* Base case: stop when indices meet or cross */
    if (left_pos >= right_pos)
        return;

    /* Swap characters */
    temp = s[left_pos];
    s[left_pos] = s[right_pos];
    s[right_pos] = temp;

    /* Recurse on the inner substring */
    reverse_r(s, left_pos + 1, right_pos - 1);
}
