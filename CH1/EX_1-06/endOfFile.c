#include <stdio.h>

int main()
{
	int c = (getchar() != EOF);
	if (c == 0)
		printf("EOF = 0");
	else if(c == 1)
		printf("EOF = 1");
	else
		printf("EOF != 0 nor 1");
	return 0;
}
