#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES   100
#define MAXLEN     100

int getLine(char line[], int lim);
int readLines(char *lines[], int maxLines);
char *alloc(int len);
void writeLines(char *lines[], int nlines);

void my_qsort(void *v[], int left, int right, int (*comp)(void *, void *));
void reverseLines(void *v[], int n);
void swap(void *v[], int i, int j);
int numcmp(char *s1, char *s2);
int charcmp(char *s1, char *s2);
int findField(char* line, int field, char* ret_buf);
int isNumber(char *s);

int fold = 0;
int dir_order = 0;
int field = 0;

int main(int argc, char *argv[])
{
    int nlines;
    char *lines[MAXLINES];
    int numeric = 0;
    int reverse = 0;
   
    /* Parse command-line options. */
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
            numeric = 1;          /* Numeric comparison */
        else if (strcmp(argv[i], "-r") == 0)
            reverse = 1;          /* Reverse output order */
        else if(strcmp(argv[i], "-f") == 0)
			fold = 1;			  /* Case in-sensitive comparsion */
		else if(strcmp(argv[i], "-d") == 0)
			dir_order = 1;		  /* Directory Order comparsion */		
		else if (strcmp(argv[i], "-k") == 0)
		{
		    if (++i >= argc || !isNumber(argv[i]))
		    {
		        printf("Missing or invalid field number\n");
		        return 1;
		    }
		    field = atoi(argv[i]);
		}
        else
        {
            printf("Unknown option %s\n", argv[i]);
            return 1;
        }
    }

    /* Select the appropriate comparison function. */
    int (*fptr)(void *, void *) = (numeric ? numcmp : charcmp);

    /* Read, sort, optionally reverse, then print the lines. */
    if ((nlines = readLines(lines, MAXLINES)) >= 0)
    {
       my_qsort((void **)lines, 0, nlines - 1, fptr);

        if (reverse)
            reverseLines((void **)lines, nlines);

        writeLines(lines, nlines);
    }
    else
        printf("Input too big\n");

    return 0;
}


/*
 * Sort an array of pointers using quicksort.
 * The comparison function determines the ordering.
 */
void my_qsort(void *v[], int left, int right,
              int (*comp)(void *, void *))
{
    if (left >= right)
        return;

    /* Choose the middle element as the pivot. */
    int pivot = left + (right - left) / 2;
    int last = left;

    /* Move the pivot to the beginning. */
    swap(v, left, pivot);

    /* Partition the array around the pivot. */
    for (int i = left + 1; i <= right; i++)
    {
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }

    /* Put the pivot into its final position. */
    swap(v, left, last);

    /* Recursively sort the two partitions. */
    my_qsort(v, left, last - 1, comp);
    my_qsort(v, last + 1, right, comp);
}


/*
 * Reverse the order of the array.
 * Used to implement the -r option.
 */
void reverseLines(void *v[], int n)
{
    int i;

    for (i = 0; i < n / 2; i++)
        swap(v, i, n - i - 1);
}


/* Exchange two elements in an array of pointers. */
void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


/*
 * Compare two strings numerically.
 * If a field is selected (-k), compare only that field.
 * Returns:
 *   >0 if s1 > s2
 *   <0 if s1 < s2
 *    0 if equal
 */
int numcmp(char *s1, char *s2)
{
    char field1[MAXLEN];
    char field2[MAXLEN];

    /* Extract the requested field if -k was specified. */
    if (field > 0)
    {
        if (findField(s1, field, field1))
            s1 = field1;
        else
            s1 = "";

        if (findField(s2, field, field2))
            s2 = field2;
        else
            s2 = "";
    }

    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 > v2)
        return 1;
    else if (v1 < v2)
        return -1;
    else
        return 0;
}

/*
 * Compare two strings.
 * Supports:
 *   -f : case-insensitive comparison
 *   -d : directory order comparison
 *   -k : compare only the specified field
 */
int charcmp(char *s1, char *s2)
{
    char field1[MAXLEN];
    char field2[MAXLEN];

    /* Extract the requested field if -k was specified. */
    if (field > 0)
    {
        if (findField(s1, field, field1))
            s1 = field1;
        else
            s1 = "";

        if (findField(s2, field, field2))
            s2 = field2;
        else
            s2 = "";
    }

    /* Compare the selected strings character by character. */
    for (;;)
    {
        /* Skip characters that are not letters, digits,
         * or blanks when directory order is enabled.
         */
        if (dir_order)
        {
            while (*s1 &&
                   !isalnum((unsigned char)*s1) &&
                   *s1 != ' ')
                s1++;

            while (*s2 &&
                   !isalnum((unsigned char)*s2) &&
                   *s2 != ' ')
                s2++;
        }

        /* Both strings ended at the same time. */
        if (*s1 == '\0' && *s2 == '\0')
            return 0;

        /* Convert characters to uppercase only when
         * case-insensitive comparison is requested.
         */
        int c1 = fold
               ? toupper((unsigned char)*s1)
               : (unsigned char)*s1;

        int c2 = fold
               ? toupper((unsigned char)*s2)
               : (unsigned char)*s2;

        /* Characters differ. */
        if (c1 != c2)
            return c1 - c2;

        s1++;
        s2++;
    }
}

/*
 * Read a line and return its length.
 */
int getLine(char line[], int lim)
{
    int c, i;
    int len = 0;

    for(i = 0; i < lim - 1 &&
                (c = getchar()) != EOF &&
                c != '\n'; i++)
    {
        line[i] = c;
        len++;
    }

    if (c == '\n')
    {
        line[i++] = c;
        len++;
    }

    line[i] = '\0';
    return len;
}


/*
 * Read all input lines and store them in dynamically
 * allocated memory obtained from alloc().
 */
int readLines(char *lines[], int maxLines)
{
    int len, nlines = 0;
    char *p;
    char line[MAXLEN];

    while((len = getLine(line, MAXLEN)) > 0)
    {
        if(nlines >= maxLines || (p = alloc(len)) == NULL)
            return -1;

        /* Remove the trailing newline. */
        if(len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        strcpy(p, line);
        lines[nlines++] = p;
    }

    return nlines;
}


/* Simple allocator. */

#define ALLOCSIZE 10000

char allocBuf[ALLOCSIZE];
char *allocp = allocBuf;


/*
 * Allocate len bytes from a fixed-size buffer.
 * Returns NULL if there is not enough space.
 */
char *alloc(int len)
{
    if(allocBuf + ALLOCSIZE - allocp >= len)
    {
        allocp += len;
        return allocp - len;
    }

    return NULL;
}


/*
 * Print all stored lines.
 */
void writeLines(char *lines[], int nlines)
{
    while(nlines--)
        printf("%s\n", *lines++);
}


int findField(char* line, int field, char* ret_buf)
{
	int current_field = 0;
	char* p = ret_buf;
	while(*line)
	{
		/* Skip white spaces */
		while(isspace((unsigned char)*line))
			line++;
			
		if(*line == '\0')
			return 0;
		
		current_field++;
		if(current_field == field)
		{
			while (*line && !isspace(*line))
				*p++ = *line++;
			
			*p = '\0';
			return 1;
		}
		
		while(*line && !isspace((unsigned char)*line))
			line++;
	}
	
	return 0;
}


int isNumber(char *s)
{
    if (*s == '\0')
        return 0;

    while (*s)
    {
        if(!isdigit((unsigned char)*s))
            return 0;
        s++;
    }

    return 1;
}

