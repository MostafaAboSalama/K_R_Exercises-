#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER      1
#define MAXOP       100
#define MAXSTACK    100
#define MAXBUF      100

/* Stack functions */
void push(double num);
double pop(void);

/* Input functions */
int getop(char s[]);
int getch(void);
void ungetch(int c);

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

        case '\n':
            printf("\t%.8g\n", pop());
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

/* Read the next operator or numeric operand. */
int getop(char s[])
{
    int c, i = 0;

    /* Skip blanks and tabs. */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    /* Handle operators and negative numbers. */
    if (!isdigit(c) && c != '.') 
    {

        if (c == '-') 
        {

            /* Look ahead one character. */
            if (!isdigit(c = getch()) && c != '.') 
            {
                ungetch(c);
                return '-';
            }

            /* '-' is the sign of a negative number. */
            s[++i] = c;
        }
        else
            return c;

    }

    /* Collect integer part. */
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    /* Collect fractional part. */
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    /* Terminate the string. */
    s[i] = '\0';

    /* Put back the first character after the number. */
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

/* Push a character back onto the input buffer. */
void ungetch(int c)
{
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
