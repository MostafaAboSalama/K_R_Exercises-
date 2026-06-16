#include <stdio.h>

int main()
{
	printf("HI\c");
	return 0;
}

/* First there is a warning 
 * warning: unknown escape sequence: '\c'
 *   5 |         printf("HI\c");
 *     |                      ^
 *
 * Output : HIc 
 */
