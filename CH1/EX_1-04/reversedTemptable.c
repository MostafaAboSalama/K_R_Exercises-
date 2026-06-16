#include <stdio.h>

int main()
{
	float fahr, celisus;
	int lower, upper, step;
	lower = 0;
	upper = 300;
	step = 20;
	
	celisus = lower;
	
	printf("Celisus	  Fahr\n");
	
	while(fahr <= upper)
	{
		fahr = (9.0 / 5.0) * celisus + 32.0;
		printf("%3.0f 	%6.1f\n", celisus, fahr);
		celisus += step;
	}
	return 0;
}
