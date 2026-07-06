#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAXSTACK    100

/* Stack functions */
void push(double num);
double pop(void);

/* Operand stack */
double stack[MAXSTACK];
int sp = 0;

int main(int argc, char *argv[])
{
    char *token;
    double op2;

    /* Process each command-line argument as an operand or operator. */
    while (--argc > 0)
    {
        token = *++argv;

        /* A single-character token matching an operator. */
        if (strlen(token) == 1 && strchr("+-*/%", token[0]))
        {
            switch (*token)
            {
                case '+':
                    push(pop() + pop());
                    break;

                case '-':
                    op2 = pop();             /* Preserve operand order. */
                    push(pop() - op2);
                    break;

                case '*':
                    push(pop() * pop());
                    break;

                case '/':
                    op2 = pop();             /* Preserve operand order. */
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        printf("Error: division by zero.\n");
                    break;

                case '%':
                    op2 = pop();             /* Floating-point remainder. */
                    if (op2 != 0.0)
                        push(fmod(pop(), op2));
                    else
                        printf("Error: division by zero.\n");
                    break;
            }
        }
        else
        {
            /* Token is an operand. */
            push(atof(token));
        }
    }

    /* Final result. */
    printf("\t%.8g\n", pop());

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
