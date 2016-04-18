// kk.c

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ITERS 25000
#define SIZE 100

int main(int argc, char * argv[])
{
	if (argc == 2) // inputfile given
	{
		// read the inputfile
		// run kk
		printf("Inputfile given\n");
	}
	else if (argc == 1) // no inputfile given; run comparisons
	{
		// generate 50 random instances of size 100
		// run all of the algorithms on each instance
		printf("No inputfile given\n");
	}
	else
	{
		printf("Invalid input\n");
	}
}

// Karmarkar-Karp
unsigned int kk(uint64_t array[])
{
	uint64_t diffArray[SIZE] = malloc(SIZE * sizeof(uint64_t));
	return 0;
}

// Repeated random
unsigned int random(uint64_t array[])
{
	for (unsigned int i = 0; i < ITERS; ++i)
	{

	}
	return 0;
}

// Hill-climbing
unsigned int hc(uint64_t array[])
{
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		
	}
	return 0;
}

// Simulated annealing
unsigned int sa(uint64_t array[])
{
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		
	}
	return 0;
}