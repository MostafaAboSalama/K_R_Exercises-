#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#define LIMIT	20
void format(void);

int main(int argc, char *argv[])
{
    format();
    
    return 0;
}


void format(void)
{
    int c;
	int printed_chars = 0;
    while ((c = getchar()) != EOF)
    {
		/* non-graphic chars */
		if(!isprint(c) && c != '\n')
		{
			/* convert to hex */
			printf("\\x%02X", c);
			printed_chars += 4;
		}
		else if(c == '\n')
		{
			putchar(c);
			printed_chars = 0;
		}
		else
		{
			putchar(c);
			printed_chars++;
		}
		/* long lines */
		if (printed_chars >= LIMIT)
	    {
	        putchar('\n');
	        printed_chars = 0;
	    }
	}
 
}
