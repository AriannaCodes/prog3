// kk.c

#include <stdio.h>

int main(int argc, char * argv[])
{
	if (argc == 2) // inputfile given
	{
		// read the inputfile
		// run kk
		printf("Inputfile given\n");
	}
	else if (argc == 1)
	{
		// generate 50 random instances of size 100
		// find kk
		// run the other algorithms at least 25k times
		printf("No inputfile given\n");
	}
	else
	{
		printf("Invalid input\n");
	}
}

// Karmarkar-Karp
unsigned int kk()
{
	return 0;
}

// Repeated random
unsigned int random()
{
	return 0;
}

// Hill-climbing
unsigned int hc()
{
	return 0;
}

// Simulated annealing
unsigned int sa()
{
	return 0;
}