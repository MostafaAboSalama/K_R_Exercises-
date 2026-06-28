#include <stdio.h>

/* EX 3-2
 * escape()   : convert real tabs and newlines into the visible
 *              escape sequences '\t' and '\n'.
 *
 * unescape() : perform the reverse transformation, converting
 *              the visible sequences '\t' and '\n' back into
 *              actual tab and newline characters.
 */
void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main(void)
{
    char original[] = "\tStart\nMiddle\tEnd\n";
    char escaped[100];
    char restored[100];

    escape(original, escaped);

    printf("Original:\n");
    printf("%s\n", original);

    printf("\nEscaped:\n");
    printf("%s\n", escaped);

    unescape(escaped, restored);

    printf("\nRestored:\n");
    printf("%s\n", restored);

    return 0;
}

/*
 * Copy s to t.
 *
 * Replace:
 *      '\t' -> "\\t"
 *      '\n' -> "\\n"
 *
 * Since one source character may expand into two destination
 * characters, separate indices (i and j) are required.
 */
void escape(char s[], char t[])
{
    int i = 0, j = 0;

    while (s[i] != '\0')
    {
        switch (s[i])
        {
        case '\t':
            t[j] = '\\';
            t[++j] = 't';
            break;

        case '\n':
            t[j] = '\\';
            t[++j] = 'n';
            break;

        default:
            t[j] = s[i];
            break;
        }

        i++;
        j++;
    }

    t[j] = '\0';
}

/*
 * Copy s to t.
 *
 * Replace:
 *      "\\t" -> '\t'
 *      "\\n" -> '\n'
 *
 * When a backslash is found, inspect the following character
 * to determine whether the pair represents an escape sequence.
 *
 * Since two source characters may collapse into one destination
 * character, i and j do not necessarily advance at the same rate.
 */
void unescape(char s[], char t[])
{
    int i = 0, j = 0;

    while (s[i] != '\0')
    {
        switch (s[i])
        {
        case '\\':
            switch (s[i + 1])
            {
            case 'n':
                t[j] = '\n';
                i++;
                break;

            case 't':
                t[j] = '\t';
                i++;
                break;

            default:
                t[j] = s[i];
                break;
            }
            break;

        default:
            t[j] = s[i];
            break;
        }

        i++;
        j++;
    }

    t[j] = '\0';
}
