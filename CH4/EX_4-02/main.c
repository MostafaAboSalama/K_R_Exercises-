#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

double my_atof(char s[]);
int getLine(char s[], int lim);

int main(void)
{
    char s[MAXLINE];

    printf("Enter a number: ");
    getLine(s, MAXLINE);

    printf("Result = %g\n", my_atof(s));

    return 0;
}

/*
 * Read a line into s and return its length.
 */
int getLine(char s[], int lim)
{
    int c, i = 0;

    while ((c = getchar()) != EOF &&
           c != '\n' &&
           i < lim - 1)
    {
        s[i++] = c;
    }

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}

/*
 * Convert ASCII string to double.
 *
 * Supports:
 *      123
 *      -123
 *      123.45
 *      -123.45
 *      1e10
 *      1.23e-4
 */
double my_atof(char s[])
{
    double val = 0.0;
    double fraction_power = 1.0;
    double scientific_power = 1.0;

    int i = 0;
    int sign = 1;

    int scientific_sign = 1;
    int exponent = 0;

    /* Skip leading whitespace */
    while (isspace(s[i]))
        i++;

    /* Get sign */
    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    /* Collect integer part */
    while (isdigit(s[i]))
    {
        val = 10.0 * val + (s[i] - '0');
        i++;
    }

    /* Decimal point */
    if (s[i] == '.')
        i++;

    /* Collect fractional part */
    while (isdigit(s[i]))
    {
        val = 10.0 * val + (s[i] - '0');
        fraction_power *= 10.0;
        i++;
    }

    /*
     * Scientific notation:
     * Example:
     *      123.45e-6
     *            ^
     */
    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;

        /* Exponent sign */
        scientific_sign = (s[i] == '-') ? -1 : 1;

        if (s[i] == '+' || s[i] == '-')
            i++;

        /* Collect exponent digits */
        while (isdigit(s[i]))
        {
            exponent = 10 * exponent + (s[i] - '0');
            i++;
        }

        /* Compute 10^exponent */
        while (exponent-- > 0)
            scientific_power *= 10.0;
    }

    /* Base number before scientific adjustment */
    val = sign * val / fraction_power;

    /* Apply exponent */
    if (scientific_sign == 1)
        val *= scientific_power;
    else
        val /= scientific_power;

    return val;
}
