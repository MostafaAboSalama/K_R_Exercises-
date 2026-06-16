#include <stdio.h>

/* EX2-9 */

int bitcount(unsigned int x);

int main()
{
	int x;
	printf("Enter a number : ");
	scanf("%d", &x);
	printf("Number of ones = %d\n", bitcount(x));
	
	return 0;
}

int bitcount(unsigned int x)
{
	int b = 0;
	while (x != 0)
    {
        x &= (x - 1);
        b++;
    }
	
	return b;
}
