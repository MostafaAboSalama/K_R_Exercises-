#include <stdio.h>

int strend(char *s, char *t);

int main(void)
{
    printf("%d\n", strend("hello", "lo"));     // 1
    printf("%d\n", strend("hello", "ell"));    // 0
    printf("%d\n", strend("hello", "hello"));  // 1
    printf("%d\n", strend("hello", "world"));  // 0

    return 0;
}

int strend(char *s, char *t)
{
    char *ps = s;   /* beginning of s */
    char *pt = t;   /* beginning of t */

    /* move to end of s */
    while (*ps)
        ps++;

    /* move to end of t */
    while (*pt)
        pt++;

    /* compare backwards */
    while (t < pt && s < ps)
    {
        if (*--ps != *--pt)
            return 0;
    }

    /* all of t matched */
    return (t == pt);
}
