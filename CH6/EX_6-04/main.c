#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXBUF      100
#define MAXWORD     100


typedef struct tnode
{
    char *word;           /* First n characters (group key) */
    struct tnode *left;
    struct tnode *right;
    int cnt;
} tnode;


int getWord(char *word, int lim);
void ungetch(int c);
int getch(void);
tnode *addtree(tnode *pnode, char *word);
void storeInArray(tnode *root, tnode **array, int *idx);
void my_qsort(tnode **array, int left, int right);
void swap(tnode** array, int i, int j);
void printSortedArray(tnode **array, int n);
int treeSize(tnode *root);
tnode *talloc(void);

int main(int argc, char **argv)
{
    tnode *root = NULL;
    char word[MAXWORD];
    int idx = 0;
    tnode **array;

    /* Build the frequency tree. */
    while (getWord(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]) || word[0] == '_')
            root = addtree(root, word);
    }

    /* Copy tree nodes into an array for sorting. */
    int n = treeSize(root);
    array = malloc(n * sizeof(*array));

    storeInArray(root, array, &idx);

    /* Sort by descending frequency. */
    my_qsort(array, 0, idx - 1);

    /* Print the sorted result. */
    printSortedArray(array, idx);

    return 0;
}

/*
 * Reads the next token.
 * - Returns identifiers.
 * - Skips strings and comments.
 * - Ignores function names.
 */
int getWord(char* word, int lim)
{
	char* w = word;
	int c;
	
	while (isspace(c = getch()))   /* skip whitespace */
		;
		
		
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


/* Build a BST keyed by words, counting repeated occurrences. */
tnode *addtree(tnode *pnode, char *word)
{
    int cond;

    if (pnode == NULL)
    {
        /* First occurrence of this word. */
        pnode = talloc();
        pnode->word = strdup(word);
        pnode->left = pnode->right = NULL;
        pnode->cnt = 1;
    }
    else if ((cond = strcmp(word, pnode->word)) == 0)
    {
        /* Word already exists. */
        pnode->cnt++;
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

/* Traverse the tree and store pointers to every node. */
void storeInArray(tnode *root, tnode **array, int *idx)
{
    if (root == NULL)
        return;

    array[*idx] = root;
    (*idx)++;

    storeInArray(root->left, array, idx);
    storeInArray(root->right, array, idx);
}

tnode *talloc(void)
{
    return (tnode *)malloc(sizeof(tnode));
}


/* Quicksort an array of tree-node pointers by frequency. */
void my_qsort(tnode **array, int left, int right)
{
    if (left >= right)
        return;

    /* Choose the middle element as the pivot. */
    int pivot = left + (right - left) / 2;
    int last = left;

    /* Move the pivot to the front. */
    swap(array, left, pivot);

    /* Partition the array. */
    for (int i = left + 1; i <= right; i++)
    {
        if (array[i]->cnt > array[left]->cnt)
            swap(array, ++last, i);
    }

    /* Place the pivot in its final position. */
    swap(array, left, last);

    my_qsort(array, left, last - 1);
    my_qsort(array, last + 1, right);
}

void swap(tnode** array, int i, int j)
{
	tnode* temp;
	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void printSortedArray(tnode **array, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d : %s\n", array[i]->cnt, array[i]->word);
}

int treeSize(tnode *root)
{
    if (root == NULL)
        return 0;

    return 1 + treeSize(root->left) + treeSize(root->right);
}
