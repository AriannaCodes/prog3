// kk.c

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITERS 25000
#define SIZE 100

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
	uint64_t * diffArray = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
	return 0;
}

// Repeated random
unsigned int rrandom(uint64_t array[])
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