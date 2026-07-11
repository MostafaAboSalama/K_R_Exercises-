/*
 * K&R Exercise 5-20 -- dcl.c with type-qualifier support
 *
 * Reads a C declaration (one per line, e.g. "char *argv[]" or
 * "const unsigned char *msg") and prints its English description.
 *
 * Changes from the plain book version:
 *   1. isKeyword()   -- recognizes base types AND qualifiers (const, volatile)
 *   2. gettoken()    -- gained one-token pushback (see ungettoken)
 *   3. main()        -- gathers a whole run of keyword tokens into datatype
 *                        instead of just one, so "const char", "unsigned
 *                        long int", etc. all get captured correctly
 *
 * dcl() and dirdcl() are untouched from the standard structure.
 *
 * Known limitation: a qualifier placed AFTER a '*' (e.g. "char * const p")
 * binds to that specific pointer rather than the base type, and isn't
 * handled here yet -- ask if you want that version too.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);
void ungettoken(void);
int getch(void);
void ungetch(int);
int isKeyword(char *word);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

/* ---- character-level pushback (unchanged from the book) ---- */

char buf[MAXTOKEN];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= MAXTOKEN)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* ---- keyword table ---- */

int isKeyword(char *word)
{
    char *keywords[] =
    {
        "char",
        "int",
        "float",
        "double",
        "long",
        "short",
        "signed",
        "unsigned",
        "const",
        "volatile",
        "void"
    };
    int size = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < size; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

/* ---- new: one-token pushback, same idea as ungetch ---- */

int tokenpushed = 0;

void ungettoken(void)
{
    tokenpushed = 1;
}

/* ---- tokenizer ---- */

int gettoken(void)
{
    int c;
    char *p = token;

    if (tokenpushed)
    {
        tokenpushed = 0;
        return tokentype;
    }

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[')
    {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c))
    {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

/* ---- recursive-descent parser (unchanged) ---- */

void dcl(void)
{
    int ns;
    for (ns = 0; gettoken() == '*'; )
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void)
{
    int type;

    if (tokentype == '(')
    {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

/* ---- driver ---- */

int main(void)
{
    while (gettoken() != EOF)
    {
        strcpy(datatype, token);

        while (gettoken() == NAME && isKeyword(token))
        {
            strcat(datatype, " ");
            strcat(datatype, token);
        }
        ungettoken();               /* put back whatever ended the run */

        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s:%s %s\n", name, out, datatype);   /* out has a leading space when non-empty */
    }
    return 0;
}
