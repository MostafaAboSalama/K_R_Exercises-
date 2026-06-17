
#include <stdio.h>

int rmvComments(void);

int main(void)
{
    printf("Enter C code (Ctrl+D to finish on Linux):\n\n");

    rmvComments();

    return 0;
}

int rmvComments(void)
{
    enum state
    {
        NORMAL,
        SAW_SLASH,
        IN_COMMENT,
        MAYBE_END_COMMENT,
        IN_STRING,
        IN_CHAR
    };

    enum state state = NORMAL;

    int c;
    int len = 0;

    while ((c = getchar()) != EOF)
    {
        switch (state)
        {
        case NORMAL:
            if (c == '/')
            {
                /* Could be the start of a comment */
                state = SAW_SLASH;
            }
            else if (c == '"')
            {
                /* Enter string literal */
                putchar(c);
                len++;
                state = IN_STRING;
            }
            else if (c == '\'')
            {
                /* Enter character constant */
                putchar(c);
                len++;
                state = IN_CHAR;
            }
            else
            {
                /* Ordinary source character */
                putchar(c);
                len++;
            }
            break;

        case SAW_SLASH:
            if (c == '*')
            {
                /* Confirmed comment start: "/*" */
                state = IN_COMMENT;
            }
            else
            {
                /* Previous '/' was not part of a comment */
                putchar('/');
                putchar(c);
                len += 2;
                state = NORMAL;
            }
            break;

        case IN_COMMENT:
            if (c == '*')
            {
                /* Possible end of comment */
                state = MAYBE_END_COMMENT;
            }
            break;

        case MAYBE_END_COMMENT:
            if (c == '/')
            {
                /* Confirmed comment end: "\/*" */
                state = NORMAL;
            }
            else if (c != '*')
            {
                /*
                 * Not the end of the comment.
                 * Return to comment state.
                 */
                state = IN_COMMENT;
            }
            /*
             * If another '*' appears, remain in
             * MAYBE_END_COMMENT.
             */
            break;

        case IN_STRING:
            putchar(c);
            len++;

            if (c == '"')
                state = NORMAL;

            break;

        case IN_CHAR:
            putchar(c);
            len++;

            if (c == '\'')
                state = NORMAL;

            break;
        }
    }

    /*
     * Handle a trailing slash before EOF:
     *
     * Input:
     *      x = a /
     *
     * leaves us in SAW_SLASH when EOF arrives.
     */
    if (state == SAW_SLASH)
    {
        putchar('/');
        len++;
    }

    return len;
}
