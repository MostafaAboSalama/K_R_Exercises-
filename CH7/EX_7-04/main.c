#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmt, ...);

int main(void)
{
    int age;
    double grade;
    char name[50];
    char ch;

    printf("Enter age, grade, name, and a character:\n");

    minscanf("%d %f %s %c", &age, &grade, name, &ch);

    printf("\nYou entered:\n");
    printf("Age   : %d\n", age);
    printf("Grade : %.2f\n", grade);
    printf("Name  : %s\n", name);
    printf("Char  : %c\n", ch);

    return 0;
}


void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sp, *cp;
    int *ip;
    double *dp;

    va_start(ap, fmt);

    for (p = fmt; *p; p++)
    {
        if (*p != '%')
            continue;

        p++;

        switch (*p)
        {
        case 'd':
            ip = va_arg(ap, int *);
            scanf("%d", ip);
            break;

        case 'f':
            dp = va_arg(ap, double *);
            scanf("%lf", dp);
            break;

        case 's':
            sp = va_arg(ap, char *);
            scanf("%s", sp);
            break;

        case 'c':
            cp = va_arg(ap, char *);
            scanf(" %c", cp);      /* Skip leading whitespace */
            break;

        case '%':
            scanf("%%");
            break;

        default:
            break;
        }
    }

    va_end(ap);
}
