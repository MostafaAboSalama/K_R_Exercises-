/* K&R Exercise 6-6 -- simple #define processor (no arguments). */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXBUF      100
#define MAXWORD     100
#define HASHSIZE 101
int echo = 1;

typedef struct nlist
{
    char *name;
    char *defn;
    struct nlist *next;
} ST_Nlist;

ST_Nlist *hashtable[HASHSIZE];
unsigned int hash(char *s);
ST_Nlist *lookup(char *s);
ST_Nlist *install(char *name, char *defn);

int getWord(char* word, int lim);
void ungetch(int c);
int getch(void);
/* Character pushback buffer */
char buffer[MAXBUF];
int bufp = 0;

int main(void)
{
    int type, c;
    char word[MAXWORD];
    while ((type = getWord(word, MAXWORD - 1)) != EOF)  /* reserves a byte for getWord's '\0' */
	{
	    if (type == '#')
	    {
	        echo = 0;
	        getWord(word, MAXWORD - 1);          
	
	        if (strcmp(word, "define") == 0)
	        {
	            
	            char name[MAXWORD];
				char defn[MAXWORD];
	            getWord(name, MAXWORD - 1);      // macro name 
				int i = 0;
				while (isspace(c = getch()) && c != '\n')
				    ;
				
				if (c != '\n' && c != EOF)
				{
				    defn[i++] = c;
				    while ((c = getch()) != '\n' && c != EOF && i < MAXWORD - 1)
				        defn[i++] = c;
				}
				defn[i] = '\0';
				install(name, defn);
				echo = 1;
	        }
	        else
	        {
	            while ((c = getch()) != '\n' && c != EOF)
					;
	            echo = 1;   
	        }
	    }
	    else if (isalpha(word[0]) || word[0] == '_')
	    {
	        
	        ST_Nlist* np;
	        if ((np = lookup(word)) != NULL)
	            printf("%s", np->defn);
	        else
	            printf("%s", word);
	    }
	    else
	        printf("%s", word);
	}
    return 0;
}
/* getWord: reads next word into `word`; returns word[0], the character
 * itself for a single-char token, or EOF at end of input.
 */
int getWord(char* word, int lim)
{
	char* w = word;
	int c;
	
	while (isspace(c = getch()))   /* skip whitespace */
	{	
		if (echo)
			putchar(c);
	}	
	if (c == EOF)
        return EOF;
        
        
	*w++ = c;
	
	
	if(!isalpha(c) && c != '_')    /* lone punctuation is its own token */
	{
		*w = '\0';
		return c;
	}
	
	while(--lim)
	{
		if(!isalnum(*w = getch()) && *w != '_')
		{
			ungetch(*w);
			break;
		}
		w++;
	}
	
	*w = '\0';
	return word[0]; 
}
/* Compute the hash value for a string. */
unsigned int hash(char *s)
{
    unsigned hash;
    for (hash = 0; *s; s++)
        hash = *s + 31 * hash;
    return hash % HASHSIZE;
}
/* Find a name in the hash table. */
ST_Nlist *lookup(char *s)
{
    ST_Nlist *np;
    for (np = hashtable[hash(s)]; np; np = np->next)
        if (strcmp(np->name, s) == 0)
            return np;
    return NULL;
}
/* Install a new name or replace its definition. */
ST_Nlist *install(char *name, char *defn)
{
    ST_Nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL)
    {
        np = (ST_Nlist *)malloc(sizeof(ST_Nlist));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtable[hashval];
        hashtable[hashval] = np;
    }
    else
    {
        free((void *)np->defn);
    }
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
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
