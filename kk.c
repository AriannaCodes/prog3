// kk.c

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// from http://stackoverflow.com/questions/7920860/how-to-generate-large-random-numbers-c
uint64_t gen() 
{
	uint64_t num;
	num = rand();
	return ((num << 32) + rand()) % 1000000000000;
}

int main(int argc, char * argv[])
{
	// seed random number generator
	time_t t;
	t = time(NULL);
	srand((unsigned) time(&t));

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
unsigned int rrandom()
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