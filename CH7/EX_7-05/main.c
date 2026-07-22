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

/* Character buffer */
char buffer[MAXBUF];
int bufp = 0;


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

/* Read the next operator or numeric operand.
   scanf/sscanf do the actual conversion, but %s and %lf skip ALL
   leading whitespace -- '\n' included -- so scanf alone can never
   see the newline that separates input lines. We peek one char by
   hand first to catch it before scanf gets a chance to swallow it. */
int getop(char s[])
{
    char token[100];
    double num;
    int c;

    /* Skip spaces/tabs ourselves, one char at a time. */
    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (c == EOF)
        return EOF;
    if (c == '\n')
        return '\n';        /* end of line: report it, don't touch scanf */

    ungetc(c, stdin);       /* not whitespace -- give it back to scanf */

    if (scanf("%99s", token) != 1)
        return EOF;

    if (sscanf(token, "%lf", &num) == 1)
    {
        strcpy(s, token);
        return NUMBER;
    }
    else if (strcmp(token, "@") == 0)
        return ASSIGN;
    else if (strcmp(token, "sin") == 0 ||
             strcmp(token, "exp") == 0 ||
             strcmp(token, "pow") == 0)
    {
        strcpy(s, token);
        return NAME;
    }
    else if (strlen(token) == 1 && isupper(token[0]))
    {
        /* single uppercase letter: a variable name */
        strcpy(s, token);
        return NAME;
    }
    else
        return token[0];    /* single-char operator/command */
}

