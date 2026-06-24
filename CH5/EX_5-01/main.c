#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER  '0'      // Token type representing a number
#define MAX_OP  100      // Maximum token length

void push(double n);
double pop(void);
int nextToken(char s[]);

int main(void)
{
    int i, array[10], getint(int* pn);
    for(i = 0; i < 10 && getint(&array[i]) != EOF; i++)
	;
    
    for(i = 0; i < 10 ; i++)
		printf("%d\t", array[i]);
	
    
    /*int type;
    char s[MAX_OP];
    double op2;

    // Read and process one token at a time
    while ((type = nextToken(s)) != EOF)
    {
        switch (type)
        {
            case NUMBER:
                // Convert token string to double and push onto stack
                push(atof(s));
                break;

            case '+':
                push(pop() + pop());
                break;

            case '-':
                // Preserve operand order: left - right
                op2 = pop();
                push(pop() - op2);
                break;

            case '*':
                push(pop() * pop());
                break;

            case '/':
                // Preserve operand order: left / right
                op2 = pop();

                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("Error! Division By Zero\n");

                break;

            case '\n':
                // End of expression: print result
                printf("\t%.8g\n", pop());
                break;

            default:
                printf("Error! Unknown Character %s\n", s);
                break;
        }
    }

    return 0;*/
}


/* ================= STACK ================= */

#define MAX_STACK 100

int sp = 0;                  // Points to next free stack position
double stack[MAX_STACK];

void push(double n)
{
    if (sp < MAX_STACK)
        stack[sp++] = n;     // Store value then advance stack pointer
    else
        printf("Error! Stack Full.\n");
}

double pop(void)
{
    if (sp > 0)
        return stack[--sp];  // Move back to top element then return it
    else
        printf("Error! Stack Empty.\n");

    return 0.0;
}


/* ============== TOKENIZER ============== */

int nextChar(void);
void pushBackChar(int c);

int nextToken(char s[])
{
    int i = 0, c;

    // Skip whitespace
    while ((s[0] = c = nextChar()) == ' ' || c == '\t')
        ;

    // Operator, newline, EOF, etc.
    if (!isdigit(c) && c != '.')
        return c;

    // Collect integer part
    if (isdigit(c))
        while (isdigit(s[++i] = c = nextChar()))
            ;

    // Collect fractional part
    if (c == '.')
        while (isdigit(s[++i] = c = nextChar()))
            ;

    s[i] = '\0';

    /*
     * We have read one character too far.
     *
     * Example:
     * Input: 123+
     *
     * While reading the number we consume '+'
     * to discover the number has ended.
     *
     * '+' belongs to the next token,
     * so put it back for the next call.
     */
    if (c != EOF)
        pushBackChar(c);

    return NUMBER;
}


/* ============== INPUT BUFFER ============== */

#define BUF_SIZE 100

char buffer[BUF_SIZE];
int bufp = 0;     // Number of characters currently in buffer

int nextChar(void)
{
    /*
     * If a character was pushed back,
     * return it first.
     *
     * Otherwise read fresh input.
     */
    return (bufp > 0) ? buffer[--bufp] : getchar();
}

void pushBackChar(int c)
{
    /*
     * Make a character available
     * for future reads.
     */
    if (bufp < BUF_SIZE)
        buffer[bufp++] = c;
    else
        printf("Too Many Items For PushBackChar\n");
}

int getint(int *pn)
{
	int c, sign;
	
	// Skip whitespace
    while ((c = nextChar()) == ' ' || c == '\t')
        ;

	/* Not A Number */
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
		pushBackChar(c);
		return 0;
	}
        
    sign = (c == '-' ) ? -1 : 1; 
    
    if(c == '-' || c == '+')
    {
		c = nextChar();
		if(!isdigit(c))
		{
			pushBackChar(c);
			pushBackChar((sign == 1) ? '+' : '-' );
			return 0;
		}
	}
		
    
    for(*pn = 0; isdigit(c); c = nextChar())
		*pn = *pn * 10 + (c - '0');
	
	*pn *= sign;
	
    if (c != EOF)
        pushBackChar(c);

    return c;
}
