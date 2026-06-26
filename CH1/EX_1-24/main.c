
#include <stdio.h>

#define MAX_LINE	1000

int getLine(char line[], int lim);
int syntax_error(void);

int main(void)
{
    printf("Enter C code (Ctrl+D to finish on Linux):\n\n");

    if (syntax_error())
		printf("Syntax error found.\n");
	else
		printf("No syntax errors found.\n");

    return 0;
}

int getLine(char line[], int lim)
{
    int c;
    int i = 0;
    int len = 0;

    /* Read characters until newline or EOF */
    while ((c = getchar()) != EOF && c != '\n')
    {
        /* Store only if space is available */
        if (i < lim - 1)
            line[i++] = c;

        len++;  /* always count full input length */
    }

    /* Include newline if present */
    if (c == '\n')
    {
        if (i < lim - 1)
            line[i++] = c;

        len++;
    }

    /* Null terminate the stored string */
    line[i] = '\0';

    return len;
}

int syntax_error(void)
{
    int double_quotes = 0;
    int single_quotes = 0;
    int paren = 0;
    int brace = 0;
    int bracket = 0;
    enum state
    {
        NORMAL,
        IN_COMMENT,
        MAYBE_END_COMMENT,
        IN_STRING,
        IN_CHAR
    };

    enum state state = NORMAL;

    int c, len = 0, i = 0;
    char line[MAX_LINE];
    int ret_val = 0;
	while ((len = getLine(line, MAX_LINE)) > 0)
	{
        for (i = 0; line[i] != '\0'; i++)
        {
			c = line[i];
			switch (state)
	        {
				case NORMAL:
		            /* Start of a block comment */
					if (c == '/' && line[i + 1] == '*')
					{
					    state = IN_COMMENT;
					    i++;                /* Skip '*' */
					}
		            else if (c == '"')
		            {
		                /* Enter string literal */   
		                double_quotes++;       
		                state = IN_STRING;
		            }
		            else if (c == '\'')
		            {
		                /* Enter character constant */
		                single_quotes++;
		                state = IN_CHAR;
		            }
		            else if (c == '(')
		                paren++;
		            else if (c == '{')
		                brace++;
		            else if (c == '[')
		                bracket++;
		            else if (c == ')')
		            {
						if(--paren < 0)
							ret_val = 1;
					}
		                
		            else if (c == '}')
		            {
						if(--brace < 0)
							ret_val = 1;
					}         
		            else if (c == ']')
		            {
						if(--bracket < 0)
							ret_val = 1;
					}
		            else
		            {
		                /* Ordinary source character */
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
					if (c == '\\')
				    {
				        /* Skip the escaped character */
				        if (line[i + 1] != '\0')
				            i++;
				    }
				    else if (c == '"')
				    {
				        double_quotes--;
				        state = NORMAL;
				    }
				    break;
	
				case IN_CHAR:
				    if (c == '\\')
				    {
				        /* Skip the escaped character */
				        if (line[i + 1] != '\0')
				            i++;
				    }
				    else if (c == '\'')
				    {
				        single_quotes--;
				        state = NORMAL;
				    }
				    break;
			}
		}
        
		}
            

    
	if(single_quotes || double_quotes || brace || bracket || paren || state != NORMAL) // error
		ret_val = 1;
    return ret_val;
}
