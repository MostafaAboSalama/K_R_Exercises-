#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

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
int undef(char *name);

int main(void)
{
    install("MAX", "100");
    install("MIN", "0");
    install("PI", "3.14159");

    printf("Initial table:\n");

    printf("MAX = %s\n", lookup("MAX")->defn);
    printf("MIN = %s\n", lookup("MIN")->defn);
    printf("PI  = %s\n", lookup("PI")->defn);

    printf("\nUpdating MAX...\n");
    install("MAX", "200");
    printf("MAX = %s\n", lookup("MAX")->defn);

    printf("\nDeleting MIN...\n");
    if (undef("MIN"))
        printf("MIN deleted successfully.\n");
    else
        printf("MIN not found.\n");

    if (lookup("MIN") == NULL)
        printf("MIN lookup returned NULL.\n");

    printf("\nTrying to delete MIN again...\n");
    if (!undef("MIN"))
        printf("MIN was already removed.\n");

    return 0;
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

/* Remove a name from the hash table. */
int undef(char *name)
{
    unsigned hashval = hash(name);
    ST_Nlist *curr = hashtable[hashval];
    ST_Nlist *prev = NULL;

    for (; curr; prev = curr, curr = curr->next)
    {
        if (strcmp(curr->name, name) == 0)
        {
            if (prev == NULL)
                hashtable[hashval] = curr->next;
            else
                prev->next = curr->next;

            free(curr->name);
            free(curr->defn);
            free(curr);

            return 1;
        }
    }

    return 0;
}
