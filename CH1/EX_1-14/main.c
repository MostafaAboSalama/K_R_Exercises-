/*
 * Exercise 1-14
 * Print a histogram of the frequencies of different
 * characters in the input.
 *
 * This version counts uppercase and lowercase letters
 * separately and prints a horizontal histogram.
 */

#include <stdio.h>

#define NUM_LETTERS 52

int main(void)
{
    int c;
    int charFreq[NUM_LETTERS] = {0};

    while ((c = getchar()) != EOF)
    {
        /* Count uppercase letters */
        if (c >= 'A' && c <= 'Z')
            charFreq[c - 'A']++;

        /* Count lowercase letters */
        else if (c >= 'a' && c <= 'z')
            charFreq[c - 'a' + 26]++;
    }

    /* Print uppercase histogram */
    for (int i = 0; i < 26; i++)
    {
        printf("%c | ", i + 'A');

        for (int j = 0; j < charFreq[i]; j++)
            putchar('*');

        putchar('\n');
    }

    /* Print lowercase histogram */
    for (int i = 26; i < 52; i++)
    {
        printf("%c | ", i - 26 + 'a');

        for (int j = 0; j < charFreq[i]; j++)
            putchar('*');

        putchar('\n');
    }

    return 0;
}
