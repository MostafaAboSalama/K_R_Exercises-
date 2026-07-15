#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXBUF      100
#define MAXWORD     100
int line_num = 1;      /* current input line, tracked by getWord */
char* noiseWords[] =   /* excluded from the cross-reference; must stay sorted for binsearch */
{
	"a",
	"an",
	"and",
	"are",
	"at",
	"is",
	"it",
	"of",
	"that",
	"the",
	"to",
	"was",
	"were",
	"with"
};
#define NWORDS (sizeof noiseWords / sizeof noiseWords[0])
typedef struct LineNode        /* one line number in a word's occurrence list */
{
    int line;
    struct LineNode* next;
}LineNode;
typedef struct LineList        /* linked list of lines a word appears on */
{
    LineNode *front;
    LineNode *rear;
    int count;              
}LineList;
typedef struct tnode           /* BST node: one word plus its line list */
{
    char* name;
    LineList* lines;
    struct tnode* left;
    struct tnode* right;
}tnode;
int getWord(char* word, int lim);
void ungetch(int c);
int getch(void);
tnode* addtree(tnode *pnode, char *word);
tnode *talloc(void);
LineNode* lalloc(void);
LineList* llstalloc(void);
LineNode* createLineNode();
LineList* createLineList();
void addLineNode(LineList *llst);
int binsearch(char* word, char* noiseWords[], int n);
void treeprint(tnode* pnode);
void printLines(LineList* llst);
int main()
{
	tnode* root = NULL;
    char word[MAXWORD];
	while (getWord(word, MAXWORD) != EOF)
	{
	    if (isalpha(word[0]) || word[0] == '_')    /* skip punctuation tokens */
	        root = addtree(root, word);
	}
	treeprint(root);
	return 0;
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
/* getWord: reads next word into `word`; returns word[0], the character
 * itself for a single-char token, or EOF at end of input */
int getWord(char* word, int lim)
{
	char* w = word;
	int c;
	
	while (isspace(c = getch()))   /* skip whitespace, counting newlines */
	{
	    if (c == '\n')
	        line_num++;
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
/* insert word into the BST at pnode under line_num; noise words are skipped */
tnode* addtree(tnode *pnode, char *word)
{
    if(binsearch(word, noiseWords, NWORDS) >= 0)
		return pnode;   /* noise word: leave this subtree untouched */
    int cond;
	
    if (pnode == NULL)
    {
        pnode = talloc();
        pnode->name = strdup(word);
        pnode->left = pnode->right = NULL;
        pnode->lines = createLineList();
    }
    else if ((cond = strcmp(word, pnode->name)) == 0)
    {
        LineNode* pn = pnode->lines->rear;
	    if(pn->line != line_num)   /* don't duplicate a line already recorded */
			addLineNode(pnode->lines);
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
/* thin malloc wrappers, one per node type */
tnode *talloc(void)
{
    return (tnode *)malloc(sizeof(tnode));
}
LineNode* lalloc(void)
{
    return (LineNode*)malloc(sizeof(LineNode));
}
LineList* llstalloc(void)
{
    return (LineList*)malloc(sizeof(LineList));
}
/* allocate and initialize a line node for the current line_num */
LineNode* createLineNode()
{
    LineNode* l = lalloc();
    if (l)
    {
        l->line = line_num;
        l->next = NULL;
    }
    return l;
}
/* allocate a line list and seed it with one node */
LineList* createLineList()
{
    LineList *llst = llstalloc();
    if (!llst)
        return NULL;
    LineNode *l = createLineNode();
    if (!l)
    {
        free(llst);
        return NULL;
    }
    llst->front = llst->rear = l;
    llst->count = 1;
    return llst;
}
/* append a new line number to the end of the list */
void addLineNode(LineList *llst)
{
    LineNode *l = createLineNode();
    if (l)
    {
        llst->rear->next = l;
        llst->rear = l;
        llst->count++;
    }
}
/* standard binary search; noiseWords[] must stay alphabetically sorted */
int binsearch(char* word, char* noiseWords[], int n)
{
	int cond, low, high, mid;
	low = 0;
	high = n - 1;
	while(low <= high)
	{
		mid = low + (high - low)/2;
		if((cond = strcmp(word, noiseWords[mid])) == 0)
			return mid;
		else if(cond > 0)
			low = mid + 1;
		else
			high = mid - 1;
	}
	
	return -1;
}
/* in-order traversal: prints words alphabetically with their line lists */
void treeprint(tnode *pnode)
{
    if (pnode == NULL)
        return;
    treeprint(pnode->left);
    printf("%s: ", pnode->name);
    printLines(pnode->lines);
    treeprint(pnode->right);
}
/* print one word's line numbers, space-separated */
void printLines(LineList *llst)
{
    LineNode *pn;
    for (pn = llst->front; pn; pn = pn->next)
        printf("%d ", pn->line);
    putchar('\n');
}
