#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void minprintf(char *fmt, ...);

int main(void)
{
    printf("========== Integer ==========\n");
    minprintf("%d\n", 123);
    minprintf("%8d\n", 123);
    minprintf("%05d\n", 123);

    printf("\n========== String ==========\n");
    minprintf("%s\n", "Hello");
    minprintf("%10s\n", "Hello");

    printf("\n========== Character ==========\n");
    minprintf("%c\n", 'A');
    minprintf("%5c\n", 'A');

    printf("\n========== Float ==========\n");
    minprintf("%f\n", 3.14159);
    minprintf("%12f\n", 3.14159);

    printf("\n========== Mixed ==========\n");
    minprintf("Name: %10s Age:%03d Grade:%8f\n",
              "Mostafa", 21, 98.5);

    printf("\n========== Percent ==========\n");
    minprintf("100%% Complete\n");

    return 0;
}


void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    char cval;

    int width;
    int zero_pad;

    va_start(ap, fmt);

    for (p = fmt; *p; p++)
    {
        /* Ordinary character */
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }

        p++;                /* skip '%' */

        zero_pad = 0;
        width = 0;

        /* Optional '0' flag */
        if (*p == '0')
        {
            zero_pad = 1;
            p++;
        }

        /* Collect field width */
        while (isdigit(*p))
        {
            width = width * 10 + (*p - '0');
            p++;
        }

        /* Conversion */
        switch (*p)
        {
        case 'd':
            ival = va_arg(ap, int);
            if (zero_pad)
                printf("%0*d", width, ival);
            else
                printf("%*d", width, ival);
            break;

        case 'f':
            dval = va_arg(ap, double);
            printf("%*f", width, dval);
            break;

        case 's':
            sval = va_arg(ap, char *);
            printf("%*s", width, sval);
            break;

        case 'c':
            cval = va_arg(ap, int);      /* char is promoted to int */
            printf("%*c", width, cval);
            break;

        case '%':
            putchar('%');
            break;

        default:
            putchar(*p);
            break;
        }
    }

    va_end(ap);
}
