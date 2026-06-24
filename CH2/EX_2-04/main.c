#include <stdio.h>

/*
 * Delete from s1 every character that appears in s2.
 */
void squeeze(char s1[], char s2[]);

int main(void)
{
    char s1[] = "abcdefg";
    char s2[] = "bdf";

    squeeze(s1, s2);

    printf("%s\n", s1);

    return 0;
}

void squeeze(char s1[], char s2[])
{
    int i, j, k = 0;
    int found;

    /* Examine each character in s1 */
    for (i = 0; s1[i] != '\0'; i++)
    {
        found = 0;

        /* Search for s1[i] in s2 */
        for (j = 0; s2[j] != '\0'; j++)
        {
            if (s1[i] == s2[j])
            {
                found = 1;
                break;
            }
        }

        /* Keep the character if it was not found in s2 */
        if (!found)
            s1[k++] = s1[i];
    }

    /* Terminate the modified string */
    s1[k] = '\0';
}
