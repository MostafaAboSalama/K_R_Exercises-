#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);
void undcl(void);
void error(const char *msg);

int parse_error = 0;

#define MAXTOKEN	100
int getToken(void);
int token_type;
char token[MAXTOKEN];
char name[MAXTOKEN];
char data_type[MAXTOKEN];
char out[1000];		

int getch(void);
void ungetch(int c);

/* Character buffer */
#define MAXBUF      100
char buffer[MAXBUF];
int bufp = 0;

int main(void)
{
    while (getToken() != EOF)
    {
        parse_error = 0;
        strcpy(data_type, token);
        out[0] = '\0';
        dcl();
        if (!parse_error && token_type != '\n')
            error("syntax error");
        if (!parse_error)
            printf("%s: %s%s\n", name, out, data_type);
    }
    return 0;
}

void dcl(void)
{
	int ns = 0;
	while (getToken() == '*')
		ns++;

	dirdcl();
	if (parse_error)
		return;
	while (ns--)
		strcat(out, "pointer to ");
}

void dirdcl(void)
{
    int type;
    /* direct-dcl -> ( dcl ) */
    if (token_type == '(')
    {
        dcl();
        
        if (parse_error)
            return;
        /* The recursive call should leave us at ')'. */
        if (token_type != ')')
        {
            error("missing ')'");
            return;
        }
    }
    /* direct-dcl -> NAME */
    else if (token_type == NAME)
    {
        strcpy(name, token);
    }
    else
    {
        error("expected name or (dcl)");
        return;
    }
    /* Handle any number of () or [] following the declarator. */
    while ((type = getToken()) == PARENS || type == BRACKETS)
    {
        if (type == PARENS)
        {
            strcat(out, "function returning ");
        }
        else
        {
            strcat(out, "array");
            strcat(out, token);
            strcat(out, " of ");
        }
    }
}

int getToken(void)
{
	int c;
	char *p = token;
	/* skip spaces */
	while ((c = getch()) == ' ' || c == '\t')
		;

	if (c == '(')
	{
		c = getch();
		if (c == ')')
		{
			strcpy(token, "()");
			return token_type = PARENS;
		}
		else
		{
			ungetch(c);
			return token_type = '(';
		}
	}
	else if (c == '[')
	{
		*p++ = c;
		while ((c = getch()) != ']')
		{
			if (c == EOF)
			{
				/* Unterminated "[...": input ran out. Report EOF rather
				   than looping forever / walking off the end of token[]. */
				*p = '\0';
				return token_type = EOF;
			}
			if (c == '\n')
			{
				/* Unterminated "[...": hit end of line instead of ']'.
				   Push the newline back so it's still there for whoever
				   handles recovery, and report a token type ('[') that
				   nothing expects, so it's treated as a syntax error
				   instead of silently accepted as end-of-declaration. */
				ungetch(c);
				*p = '\0';
				return token_type = '[';
			}
			if (p < token + MAXTOKEN - 1)
				*p++ = c;
		}
		if (p < token + MAXTOKEN - 1)
			*p++ = c;
		*p = '\0';
		return token_type = BRACKETS;
	}
	else if (isalpha(c))
	{
		*p++ = c;
		while (isalnum(c = getch()))
		{
			if (p < token + MAXTOKEN - 1)
				*p++ = c;
		}
		*p = '\0';
		ungetch(c);
		return token_type = NAME;
	}
	else
		return token_type = c;
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

void undcl(void)
{
	out[0] = '\0';
	char temp[MAXTOKEN];
	strcat(out, token);
	while (getToken() != '\n')
	{
		if (token_type == PARENS || token_type == BRACKETS)
			strcat(out, token);
		else if (token_type == '*')
		{
			sprintf(temp, "(*%s)", out);
			strcpy(out, temp);
		}
		else if (token_type == NAME)
		{
			sprintf(temp, "%s %s", token, out);
			strcpy(out, temp);
		}
	}

}

/* Report an error and recover by discarding the rest of the line. */
void error(const char *msg)
{
    printf("Error: %s\n", msg);
    parse_error = 1;
    /* Skip tokens until end of declaration. */
    while (token_type != '\n' && token_type != EOF)
        getToken();
}
