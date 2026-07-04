#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define NUMBER      1
#define NAME        2
#define ASSIGN      3
#define MAXOP       100
#define MAXSTACK    100
#define MAXBUF      100

double vars[26] = {0};

double lastprinted = 0.0;  /* The "most recently printed value" */

int getLine(char* line);
int my_atoi(char*s);
void itoa(int n, char* s);
void reverse(char* s);
int strrindex(char* s, char* t);

/* Stack functions */
void push(double num);
double pop(void);

/* Input functions */
int getop(char* s);
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
    
    int type;
    double op2;
    
    char s[1000];
    char t[1000];

    /* Test getline */
    printf("=== getline ===\n");
    printf("Enter a line: ");
    getLine(s);
    printf("You entered: %s\n", s);

    /* Test atoi */
    printf("\n=== atoi ===\n");
    strcpy(s, "-12345");
    printf("String: %s\n", s);
    printf("Integer: %d\n", my_atoi(s));

    /* Test itoa */
    printf("\n=== itoa ===\n");
    itoa(-98765, s);
    printf("String: %s\n", s);

    /* Test reverse */
    printf("\n=== reverse ===\n");
    strcpy(s, "Hello, World!");
    reverse(s);
    printf("Reversed: %s\n", s);

    /* Test strindex / strrindex */
    printf("\n=== strrindex ===\n");
    strcpy(s, "the quick brown fox jumps over the lazy fox");
    strcpy(t, "fox");

    printf("String    : %s\n", s);
    printf("Substring : %s\n", t);
    printf("Rightmost index = %d\n", strrindex(s, t));

	printf("\n=== getop ===\n");
	printf("Enter tokens (Ctrl+D to finish):\n");
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


/* Read a line from standard input.
 * Store at most lim - 1 characters, but return the full line length.
 */
int getLine(char* line)
{
    int c;
    int len = 0;
	char*p = line;
    /* Read characters until newline or EOF */
    while ((c = getchar()) != EOF && c != '\n')
    {
		*p++ = c;
        len++;  
    }

    /* Include newline if present */
    if (c == '\n')
    {
		*p++ = c;
        len++;
    }

    /* Null terminate the stored string */
    *p = '\0';

    return len;
}

int my_atoi(char*s)
{
	int n = 0, sign = 1;
	/* SKip spaces */
	while(*s == ' ')
		s++;
		
	sign = (*s == '-') ? -1 : 1;
	if(*s == '-' || *s == '+')
		*s++;
	while(*s && isdigit(*s))
		n = n * 10 + (*s++ - '0');
		
	return sign * 	n;

}

void itoa(int n, char* s)
{
    int i = 0;
    int sign = n;
    char*p = s;

    do {
        /* Extract the last digit. */
        int digit = n % 10;

        /* Make the digit positive before converting to a character. */
        if (digit < 0)
            digit = -digit;

        *p++ = digit + '0';

    } while ((n /= 10) != 0);

    /* Add the minus sign if the original number was negative. */
    if (sign < 0)
        *p++ = '-';

    *p = '\0';

    reverse(s);
}

/* Reverse a null-terminated string in place. */
void reverse(char *s)
{
    char *p = s;
    char *q = s + strlen(s) - 1;
    char temp;

    while (p < q)
    {
        temp = *p;
        *p = *q;
        *q = temp;

        p++;
        q--;
    }
}

/*
 * Return the position of the rightmost occurrence
 * of t in s, or -1 if there is no match.
 */
int strrindex(char* s, char* t)
{
    char* send = s + strlen(s) - 1;
	char* tend = t + strlen(t) - 1;
	
	while (send >= s)
	{
	    char* ps = send;
	    char* pt = tend;
	
	    while (ps >= s && pt >= t && *ps == *pt)
	    {
	        ps--;
	        pt--;
	    }
	
	    if (pt < t)
	        return ps - s + 1;
	
	    send--;
	}

	return -1;
}

/* Read the next operator or numeric operand. */
int getop(char* s)
{
    int c, i = 0;
	char*ps = s;
	
    /* Skip blanks and tabs. */
    while ((c = getch()) == ' ' || c == '\t')
        ;

    *ps = c;
    i = 0;

    /* Handle the assignment token first. */
    if (c == '@')
    {
        c = getch();

        if (isupper(c))
        {
            *ps++ = c;
			*ps = '\0';
            return ASSIGN;
        }

        printf("Error: expected variable after '@'.\n");

        if (c != EOF)
            ungetch(c);

        return '?';
    }

    /* Handle operators and negative numbers. */
    if (!isdigit(c) && c != '.' && !isalpha(c))
    {
        if (c == '-')
        {
            /* Look ahead one character. */
            if (!isdigit(c = getch()) && c != '.')
            {
                if (c != EOF)
                    ungetch(c);
                return '-';
            }

            /* '-' is the sign of a negative number. */
            *(++ps) = c;
        }
        else
            return c;
    }

    /* Handle names: variables (A-Z), function names (sin/exp/pow), and
       the single-letter stack commands (t/d/w/c). */
    if (isalpha(c))
    {
        *ps++ = c;                 /* Store first letter. */

        while (isalpha(c = getch()))
            *ps++ = c;

        *ps = '\0';

        if (c != EOF)
            ungetch(c);

        if (*(s + 1) == '\0' && strchr("tdwc", *s))
            return *s;

        return NAME;
    }

    /* Collect integer part. */
    if (isdigit(c))
        while (isdigit(*(++ps) = c = getch()))
            ;

    /* Collect fractional part. */
    if (c == '.')
        while (isdigit(*(++ps) = c = getch()))
            ;

    /* Terminate the string. */
    *ps = '\0';

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
