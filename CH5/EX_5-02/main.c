#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXBUF 100

/* Input functions */
int get_float(float *pfloat);
int getch(void);
void ungetch(int c);

/* Character pushback buffer */
char buffer[MAXBUF];
int bufp = 0;

int main(void)
{
    float f;
    int status;

    printf("Enter floating-point numbers (Ctrl+D to end):\n");

    while ((status = get_float(&f)) != EOF)
    {
        if (status == 0)
            printf("Not a number.\n");
        else
            printf("Value = %f\n", f);
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
int get_float(float *pfloat)
{
    int c, sign;
	float power = 1.0, val = 0.0;
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

    /* Collect intger part. */
    for (val = 0.0; isdigit(c); c = getch())
        val = 10.0 * val + (c - '0');
    
    /* Collect fraction part. */    
	if(c == '.')
	{
		c = getch();
		if(isdigit(c))
		{
			for(power = 1.0; isdigit(c); c = getch())
			{
				val = val * 10.0 + (c -'0');
				power *= 10;
			} 
		}	
	}     

    *pfloat = sign * val / power;

    /* Save the first non-digit for the next call. */
    if (c != EOF)
        ungetch(c);

    return 1;
}
