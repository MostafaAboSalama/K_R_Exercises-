#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXBUF 100

/* Input functions */
int get_int(int *pint);
int getch(void);
void ungetch(int c);

/* Character pushback buffer */
char buffer[MAXBUF];
int bufp = 0;

int main(void)
{
    int n;
    int status;

    printf("Enter values (Ctrl+D to end):\n");

    while ((status = get_int(&n)) != EOF)
    {
        if (status == 0)
            printf("Not a number.\n");
        else
            printf("Number = %d\n", n);
    }

    printf("EOF reached.\n");

    return 0;
}

/* Push a character back onto the input buffer. */
void ungetch(int c)
{
    /* EOF is a sentinel, not a real character. */
    if (c == EOF)
    {
        printf("ungetch: cannot push back EOF\n");
        return;
    }

    if (bufp < MAXBUF)
        buffer[bufp++] = c;
    else
        printf("Error: buffer full.\n");
}

/* Get a character from the buffer or stdin. */
int getch(void)
{
    if (bufp > 0)
        return buffer[--bufp];
    else
        return getchar();
}

/* Read the next integer from input. */
int get_int(int *pint)
{
    int c, sign;

    /* Skip leading whitespace. */
    while (isspace(c = getch()))
        ;

    /* Not the start of a number. */
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);
        return 0;
    }

    /* Determine the sign. */
    sign = (c == '-') ? -1 : 1;

    /* If a sign is present, the next character must be a digit. */
    if (c == '+' || c == '-')
    {
        c = getch();

        if (!isdigit(c))
        {
            /* The sign is not part of a number.
               Push back the lookahead character. */
            if (c != EOF)
                ungetch(c);

            return 0;
        }
    }

    /* Collect the digits. */
    for (*pint = 0; isdigit(c); c = getch())
        *pint = 10 * *pint + (c - '0');

    *pint *= sign;

    /* Save the first non-digit for the next call. */
    if (c != EOF)
        ungetch(c);

    return 1;
}
