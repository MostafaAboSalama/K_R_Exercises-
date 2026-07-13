#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct key 
{
    char* word;
    int cnt;
} keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"do", 0},
    {"double", 0},
    {"else", 0},
    {"enum", 0},
    {"extern", 0},
    {"float", 0},
    {"for", 0},
    {"goto", 0},
    {"if", 0},
    {"int", 0},
    {"long", 0},
    {"register", 0},
    {"return", 0},
    {"short", 0},
    {"signed", 0},
    {"sizeof", 0},
    {"static", 0},
    {"struct", 0},
    {"switch", 0},
    {"typedef", 0},
    {"union", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};



#define MAXBUF      100
#define MAXWORD     100

#define NKEYS (sizeof keytab / sizeof keytab[0])

int getWord(char* word, int lim);
void ungetch(int c);
int getch(void);
int binsearch(char* word, struct key tab[], int n);

/* Character buffer */
char buffer[MAXBUF];
int bufp = 0;



int main()
{
	int n;
	char word[MAXWORD];
	while(getWord(word, MAXWORD) != EOF)
	{
		if (isalpha(word[0]) || word[0] == '_')
		{
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].cnt++;
		}
	} 
	for(int i = 0; i < NKEYS; i++)
	{
		if(keytab[i].cnt > 0)
			printf("%4d %s\n", keytab[i].cnt, keytab[i].word);
	}
	return 0;
}

/*
	 * get first character
		if identifier
		    read identifier
		else if '"'
		    skip string
		else if '\''
		    skip character constant
		else if '/'
		    determine whether comment
		else if '#'
		    skip preprocessor
    */

int getWord(char* word, int lim)
{
	
	char* w = word;
	int c;
	
	/* Skip leading white space. */
	while(isspace(c = getch()))
		;
		
	if(c == EOF)
		return EOF;
	
	*w++ = c;
		
	if (isalpha(c) || c == '_') 
	{
	    /* Read an identifier */
	    while(--lim > 0)
		{
			if(!isalnum(*w = getch()) && *w != '_')
			{
				ungetch(*w);
				break;
			}
			w++;
		}
		
		*w = '\0';
	}
	else 
	{
	    switch (c) 
	    {
	        case '"':
	            /* String */
	            while((c = getch()) != '"' && c != EOF)
	            {
					if(c == '\\') /* Escape Sequence */
						getch();					
				}				
	            break;
	
	        case '\'':
	            /* Character constant */
	            while((c = getch()) != '\'' && c != EOF)
				{
					if(c == '\\') /* Escape Sequence */
						getch();					
				}	
	            break;
	
	        case '/':
	            /* Comment or division */
	            c = getch();
	            if(c == '*')
	            {
					while ((c = getch()) != EOF)
					{
						if(c == '*')
						{
							c = getch();
							if(c == '/')
								break;
							else
								ungetch(c);							
						}						
					}
					
				}
				else if(c == '/')
				{
					while ((c = getch()) != '\n' && c != EOF)
						;
				}
				else
					ungetch(c);
	            break;
	
	        case '#':
	            /* Preprocessor */
	            while((c = getch()) != '\n' && c != EOF)
					;
	            break;
	
	        default:
	            /* Other character */
	            break;
	    }
	    *w = '\0';
	}
		
	return word[0];
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

int binsearch(char* word, struct key tab[], int n)
{
	int cond, low, high, mid;
	low = 0;
	high = n - 1;
	while(low <= high)
	{
		mid = low + (high - low)/2;
		if((cond = strcmp(word, tab[mid].word)) == 0)
			return mid;
		else if(cond > 0)
			low = mid + 1;
		else
			high = mid - 1;
	}
	
	return -1;
}
