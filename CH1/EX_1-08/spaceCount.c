#include <stdio.h>

int main()
{
	int spaceCount = 0, tabCount = 0, newLineCount = 0;
	int c;
	
	while((c = getchar()) != EOF)
	{
		if(c == ' ')
			spaceCount++;
		else if(c == '\t')
			tabCount++;
		else if(c == '\n')
			newLineCount++;
			
	}
	
	printf("Space Count = %d	Tab Count = %d	New Line Count = %d\n", spaceCount, tabCount, newLineCount); 
	return 0;
}
