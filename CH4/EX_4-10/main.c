#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUMBER      1
#define NAME        2
#define ASSIGN      3
#define MAXOP       100
#define MAXSTACK    100
#define MAXBUF      100
#define MAXLINE  	100

double vars[26] = {0};

double lastprinted = 0.0;  /* The "most recently printed value" */


/* Stack functions */
void push(double num);
double pop(void);
void stack_top(void);
void duplicate_stack_top(void);
void swap_stack_top(void);
void clear_stack(void);

/* Input functions */
int getop(char s[]);

/* Stack */
double stack[MAXSTACK];
int sp = 0;

int getLine(char line[], int lim);

int main(void)
{
    char s[MAXOP];
    int type;
    double op2;

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;

        case '+':
            push(pop() + pop());
            break;

        case '-':
            op2 = pop();
            push(pop() - op2);
            break;

        case '*':
            push(pop() * pop());
            break;

        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("Error: division by zero.\n");
            break;

        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("Error: division by zero.\n");
            break;

        case NAME:
            if (strlen(s) == 1 && isupper(s[0]))
            {
                /* Push the value stored in the variable. */
                push(vars[s[0] - 'A']);
            }
            else if (strcmp(s, "sin") == 0)
                push(sin(pop()));
            else if (strcmp(s, "exp") == 0)
                push(exp(pop()));
            else if (strcmp(s, "pow") == 0)
            {
                op2 = pop();
                push(pow(pop(), op2));
            }
            else
                printf("Error: unknown function %s\n", s);
            break;

        case ASSIGN:
            if (sp > 0)
                vars[s[0] - 'A'] = pop();
            else
                printf("Error: stack empty on assignment to %c\n", s[0]);
            break;

        /* Print the top element without removing it. */
        case 't':
            stack_top();
            break;

        /* Duplicate the top element. */
        case 'd':
            duplicate_stack_top();
            break;

        /* Swap the top two elements. */
        case 'w':
            swap_stack_top();
            break;

        /* Clear the stack. */
        case 'c':
            clear_stack();
            break;

        /* Recall the most recently printed value (K&R 4-6). */
        case '_':
            push(lastprinted);
            break;

        /* Print and remove the top element. */
        case '\n':
            if (sp > 0)
            {
                lastprinted = pop();
                printf("\t%.8g\n", lastprinted);
            }
            break;

        default:
            printf("Error: unknown command '%c'\n", type);
            break;
        }
    }

    return 0;
}

/* Push a value onto the stack. */
void push(double num)
{
    if (sp < MAXSTACK)
        stack[sp++] = num;
    else
        printf("Error: stack full.\n");
}

/* Pop and return the top value from the stack. */
double pop(void)
{
    if (sp > 0)
        return stack[--sp];

    printf("Error: stack empty.\n");
    return 0.0;
}

/* Print the value at the top of the stack without removing it. */
void stack_top(void)
{
    if (sp > 0)
        printf("Stack Top = %g\n", stack[sp - 1]);
    else
        printf("Stack Empty.\n");
}

/* Duplicate the top element of the stack. */
void duplicate_stack_top(void)
{
    if (sp > 0 && sp < MAXSTACK)
    {
        stack[sp] = stack[sp - 1];
        sp++;
    }
    else if (sp == 0)
        printf("Stack Empty.\n");
    else
        printf("Stack Full.\n");
}

/* Swap the top two elements of the stack. */
void swap_stack_top(void)
{
    if (sp >= 2)
    {
        double temp = stack[sp - 1];
        stack[sp - 1] = stack[sp - 2];
        stack[sp - 2] = temp;
    }
    else
        printf("Need at least two elements.\n");
}

/* Remove all elements from the stack. */
void clear_stack(void)
{
    sp = 0;
}

/* Read a line from standard input.
 * Store at most lim - 1 characters, but return the full line length.
 */
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

 /* Return the next operator, number, or name from the current input line.
 * A new line is read only after all tokens from the previous one are consumed.
 */
int getop(char s[])
{
	static int line_index = 0;
	int string_index = 0;
	int c = 0;
	static char line[MAXLINE];
	
	/* Read another line when the current one has been completely processed. */
	if (line[line_index] == '\0')
	{
	    if (getLine(line, MAXLINE) == 0)
	        return EOF;
	
	    line_index = 0;
	}
	
	/* Skip blanks and tabs. */
    while ((c = line[line_index++]) == ' ' || c == '\t')
        ;

    s[0] = c;
    string_index = 0;
    
    /* End of the current input line. Reset the buffer so the next call
	* reads a new line.
	*/
    if (c == '\n')
	{
	    line_index = 0;
	    line[0] = '\0';
	    return '\n';
	}
    
    /* Handle the assignment token first. */
    if (c == '@')
    {
        c = line[line_index++];

        if (isupper(c))
        {
            s[0] = c;
            s[1] = '\0';
            return ASSIGN;
        }

        printf("Error: expected variable after '@'.\n");


        --line_index;

        return '?';
    }
    
    /* Handle operators and negative numbers. */
    if (!isdigit(c) && c != '.' && !isalpha(c))
    {
        if (c == '-')
        {
            /* Peek at the next character to distinguish subtraction from a negative number. */
            if (!isdigit(c = line[line_index++]) && c != '.')
            {
                --line_index;
                return '-';
            }

            /* '-' begins a negative number. */
            s[++string_index] = c;
        }
        else
            return c;
    }
    
    /* Handle names: variables (A-Z), function names (sin/exp/pow), and
   the single-letter stack commands (t/d/w/c). */
    if (isalpha(c))
    {
        s[string_index++] = c;                 /* Store first letter. */

        while (isalpha(c = line[line_index++]))
            s[string_index++] = c;

        s[string_index] = '\0';

        --line_index;

        if (s[1] == '\0' && strchr("tdwc", s[0]))
            return s[0];

        return NAME;
    }
    
    /* Collect integer part. */
    if (isdigit(c))
        while (isdigit(s[++string_index] = c = line[line_index++]))
            ;

    /* Collect fractional part. */
    if (c == '.')
        while (isdigit(s[++string_index] = c = line[line_index++]))
            ;

    /* Terminate the string. */
    s[string_index] = '\0';

    /* Back up to the first character after the number. It will be processed on the next call.*/
    --line_index;

    return NUMBER;

}
