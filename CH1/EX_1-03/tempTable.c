#include <stdio.h>

int main()
{
	float fahr, celisus;
	int lower, upper, step;
	lower = 0;
	upper = 300;
	step = 20;
	
	fahr = lower;
	
	printf("Fahr	Celisus\n");
	
	while(fahr <= upper)
	{
		celisus = (5.0 / 0.9) * (fahr - 32.0);
		printf("%3.0f 	%6.1f\n", fahr, celisus);
		fahr += step;
	}
	return 0;
}
