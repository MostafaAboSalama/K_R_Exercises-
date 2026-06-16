#include <stdio.h>

void tempConversion(int lower, int upper, int step);

int main()
{
	tempConversion(0, 300, 20);
	
	return 0;
}

void tempConversion(int lower, int upper, int step)
{
	float fahr, celisus;
	
	fahr = lower;
	
	printf("Fahr	Celisus\n");
	
	while(fahr <= upper)
	{
		celisus = (5.0 / 0.9) * (fahr - 32.0);
		printf("%3.0f 	%6.1f\n", fahr, celisus);
		fahr += step;
	}
}
