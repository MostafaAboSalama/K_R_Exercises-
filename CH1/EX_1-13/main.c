/*
 * Exercise 1-13
 * Print a histogram of the lengths of words in the input.
 *
 * This version counts how many words have each length and
 * prints the results as a simple table.
 */

#include <stdio.h>

#define MAX_LENGTH 30

int main(void)
{
    int c;
    int wordsOfLength[MAX_LENGTH] = {0};
    int inWord = 0;
    int cnt = 0;   /* Current word length */

    while ((c = getchar()) != EOF)
    {
        /* Word boundary reached */
        if (c == ' ' || c == '\t' || c == '\n')
        {
            if (inWord)
            {
                /* Record the completed word length */
                if (cnt < MAX_LENGTH)
                    wordsOfLength[cnt]++;

                inWord = 0;
                cnt = 0;
            }
        }
        else
        {
            /* Count characters in the current word */
            cnt++;
            inWord = 1;
        }
    }

    /* Handle a word that ends at EOF */
    if (inWord && cnt < MAX_LENGTH)
        wordsOfLength[cnt]++;

    /* Print the histogram data */
    for (int i = 1; i < MAX_LENGTH; i++)
	{
		printf("%2d | ", i);

		for (int j = 0; j < wordsOfLength[i]; j++)
			putchar('*');

		putchar('\n');
	}

    return 0;
}
