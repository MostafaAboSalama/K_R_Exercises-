#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[]);

int main(void)
{
    char out[256];

    char *tests[] = {
        "a-d", "A-D", "0-5",
        "a-z", "A-Z", "0-9",

        "-a-z", "a-z-", "---",
        "a-", "-a",

        "g-f", "9-0",
        "a-9", "A-9", "a-Z",

        "a-c-g", "a-c-g-f",
        "a-b-c", "a-b-c-d",

        "ab-d", "a-bd", "abcd",
        "5-8a-d", "A-C0-3x-z",
        ""
    };

    int ntests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < ntests; i++)
    {
        expand(tests[i], out);
        printf("Input : \"%s\"\n", tests[i]);
        printf("Output: \"%s\"\n\n", out);
    }

    return 0;
}

/*
 * Expands ranges like a-d → abcd
 * Uses last output char + next input char to validate ranges
 */
void expand(char s1[], char s2[])
{
    int s1_index = 0, s2_index = 0;
    int c1 = 0, c2;
    int iterations = 0;

    while (s1[s1_index])
    {
        if (s1[s1_index] != '-')
        {
            // copy normal character
            s2[s2_index++] = s1[s1_index++];

            // track last output character
            if (s2_index > 0)
                c1 = s2[s2_index - 1];
        }
        else
        {
            // handle leading '-'
            if (s1_index == 0)
            {
                s2[s2_index++] = '-';
                s1_index++;
                continue;
            }

            // check if '-' can form a valid range
            if (s1[s1_index + 1] != '\0')
            {
                c2 = s1[s1_index + 1];

                if (
                    s2_index > 0 &&
                    (
                        (islower(c1) && islower(c2)) ||
                        (isupper(c1) && isupper(c2)) ||
                        (isdigit(c1) && isdigit(c2))
                    )
                )
                {
                    // expand increasing range
                    if (c1 < c2)
                    {
                        iterations = c2 - c1;

                        while (iterations--)
                        {
                            s2[s2_index++] = ++c1;
                        }

                        s1_index += 2; // skip "x-y"
                    }
                    else
                    {
                        s2[s2_index++] = '-';
                        s1_index++;
                    }
                }
                else
                {
                    s2[s2_index++] = '-';
                    s1_index++;
                }
            }
            else
            {
                // trailing '-'
                s2[s2_index++] = '-';
                s1_index++;
            }
        }
    }

    s2[s2_index] = '\0';
}
