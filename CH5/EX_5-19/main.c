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
char out[100];


int getch(void);
void ungetch(int c);
/* Character buffer */
#define MAXBUF      100
char buffer[MAXBUF];
int bufp = 0;

int main(void)
{
   while(getToken() != EOF)
    { 
		undcl(); 
		printf("%s\n", out); 
	}

    return 0;
}


void dcl(void)
{
	int ns = 0;
	while(getToken() == '*')
		ns++;
	
	dirdcl();
	while(ns--)
		strcat(out, "pointer to ");
}

void dirdcl(void)
{
    int type;

    /* direct-dcl -> ( dcl ) */
    if (token_type == '(')
    {
        dcl();

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
	char* p = token;
	/* skip spaces */
	while((c = getch()) == ' ' || c == '\t')
		;
	
	if(c == '(')
	{
		c = getch();
		if(c == ')')
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
	else if(c == '[')
	{
		for(*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return token_type = BRACKETS;
	}
	else if(isalpha(c))
	{
		for(*p++ = c; isalnum(c = getch()); )
			*p++ = c;
			
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
    char temp[MAXTOKEN];

    /* Start with the identifier. */
    out[0] = '\0';
    strcpy(out, token);

    /* Process the remaining tokens until end of line. */
    while(getToken() != '\n')
    {
           /* appended to the current declaration. */
        if(token_type == PARENS || token_type == BRACKETS)
            strcat(out, token);

        /* Pointer operator. Add parentheses only if the current
           declaration already contains a postfix operator (function
           or array), since '*' has lower precedence than both. */
        else if(token_type == '*')
        {
            if (strstr(out, "()") != NULL || strchr(out, '[') != NULL)
                sprintf(temp, "(*%s)", out);
            else
                sprintf(temp, "*%s", out);

            strcpy(out, temp);
        }

        /* The final NAME token is the data type. Prefix it to the
           declaration we have built so far. */
        else if(token_type == NAME)
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
