#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXBUF      100
#define MAXWORD     100

typedef struct NameNode
{
    char *name;
    struct NameNode *next;
} NameNode;

typedef struct group
{
    NameNode *front;
    NameNode *rear;
    int count;              /* Number of distinct names in the group */
} group;

typedef struct tnode
{
    char *prefix;           /* First n characters (group key) */
    struct tnode *left;
    struct tnode *right;
    group *pgroup;
} tnode;

int n = 6;

int getWord(char *word, int lim);
void ungetch(int c);
int getch(void);
tnode *addtree(tnode *pnode, char *word);
void treeprint(tnode *pnode);

tnode *talloc(void);
NameNode *nalloc(void);
group *galloc(void);

char *my_strndup(char *str, int n);

NameNode *createName(char *fname);
group *createGroup(char *fname);
void insertName(group *pg, char *fname);
void printGroup(group *pg);

int main(int argc, char **argv)
{
    if (argc == 2)
        n = atoi(argv[1]);

    tnode *root = NULL;
    char word[MAXWORD];

    while (getWord(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]) || word[0] == '_')
            root = addtree(root, word);
    }

    treeprint(root);

    return 0;
}

/*
 * Reads the next token.
 * - Returns identifiers.
 * - Skips strings and comments.
 * - Ignores function names.
 */
int getWord(char *word, int lim)
{
    char *w = word;
    int c;

    while (isspace(c = getch()))
        ;

    if (c == EOF)
        return EOF;

    *w++ = c;

    if (isalpha(c) || c == '_')
    {
        /* Read an identifier */
        while (--lim > 0)
        {
            if (!isalnum(*w = getch()) && *w != '_')
            {
                ungetch(*w);
                break;
            }
            w++;
        }

        /* Ignore function names */
        while (isspace(c = getch()))
            ;

        if (c == '(')
            word[0] = '\0';
        else
        {
            ungetch(c);
            *w = '\0';
        }
    }
    else
    {
        switch (c)
        {
        case '"':       /* Skip string literal */
            while ((c = getch()) != '"' && c != EOF)
            {
                if (c == '\\')
                    getch();
            }
            break;

        case '/':       /* Skip comments */
            c = getch();

            if (c == '*')
            {
                while ((c = getch()) != EOF)
                {
                    if (c == '*')
                    {
                        c = getch();
                        if (c == '/')
                            break;
                        else
                            ungetch(c);
                    }
                }
            }
            else if (c == '/')
            {
                while ((c = getch()) != '\n' && c != EOF)
                    ;
            }
            else
                ungetch(c);

            break;

        default:
            break;
        }

        *w = '\0';
    }

    return word[0];
}

/* Character pushback buffer */
char buffer[MAXBUF];
int bufp = 0;

void ungetch(int c)
{
    if (bufp < MAXBUF)
        buffer[bufp++] = c;
    else
        printf("Error: buffer full.\n");
}

int getch(void)
{
    return (bufp > 0) ? buffer[--bufp] : getchar();
}

/* Insert a variable into the prefix tree */
tnode *addtree(tnode *pnode, char *word)
{
    int cond;

    /* A valid group needs characters after the first n */
    if (strlen(word) <= n)
        return pnode;

    if (pnode == NULL)
    {
        pnode = talloc();
        pnode->prefix = my_strndup(word, n);
        pnode->left = pnode->right = NULL;
        pnode->pgroup = createGroup(word);
    }
    else if ((cond = strncmp(word, pnode->prefix, n)) == 0)
    {
        insertName(pnode->pgroup, word);
    }
    else if (cond < 0)
    {
        pnode->left = addtree(pnode->left, word);
    }
    else
    {
        pnode->right = addtree(pnode->right, word);
    }

    return pnode;
}

tnode *talloc(void)
{
    return (tnode *)malloc(sizeof(tnode));
}

group *galloc(void)
{
    return (group *)malloc(sizeof(group));
}

NameNode *nalloc(void)
{
    return (NameNode *)malloc(sizeof(NameNode));
}

/* Duplicate the first n characters of a string */
char *my_strndup(char *str, int n)
{
    char *p = (char *)malloc(n + 1);

    if (p)
    {
        strncpy(p, str, n);
        p[n] = '\0';
    }

    return p;
}

/* Print groups containing more than one distinct name */
void treeprint(tnode *pnode)
{
    if (pnode)
    {
        treeprint(pnode->left);

        if (pnode->pgroup->count > 1)
            printGroup(pnode->pgroup);

        treeprint(pnode->right);
    }
}

NameNode *createName(char *fname)
{
    NameNode *n = nalloc();

    if (n)
    {
        n->name = strdup(fname);
        n->next = NULL;
    }

    return n;
}

/* Create a new group with its first name */
group *createGroup(char *fname)
{
    group *g = galloc();

    if (!g)
        return NULL;

    NameNode *n = createName(fname);

    if (!n)
    {
        free(g);
        return NULL;
    }

    g->front = g->rear = n;
    g->count = 1;

    return g;
}

/* Insert only distinct names into the group */
void insertName(group *pg, char *fname)
{
    NameNode *pn;

    for (pn = pg->front; pn; pn = pn->next)
    {
        if (strcmp(fname, pn->name) == 0)
            return;
    }

    NameNode *n = createName(fname);

    if (n)
    {
        pg->rear->next = n;
        pg->rear = n;
        pg->count++;
    }
}

void printGroup(group *pg)
{
    NameNode *pn;

    for (pn = pg->front; pn; pn = pn->next)
        printf("%s\n", pn->name);

    putchar('\n');
}

