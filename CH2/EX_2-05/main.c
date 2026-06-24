#include <stdio.h>

/*
 * Return the first position in s1 that contains
 * any character from s2.
 * Return -1 if no match exists.
 */
int any(char s1[], char s2[]);

int main(void)
{
    char s1[] = "hello";
    char s2[] = "xyzl";

    printf("%d\n", any(s1, s2));

    return 0;
}

int any(char s1[], char s2[])
{
    int i, j;

    /* Examine each character in s1 */
    for (i = 0; s1[i] != '\0'; i++)
    {
        /* Compare it with every character in s2 */
        for (j = 0; s2[j] != '\0'; j++)
        {
            /* Return the position of the first match */
            if (s1[i] == s2[j])
                return i;
        }
    }

    /* No matching character found */
    return -1;
}
