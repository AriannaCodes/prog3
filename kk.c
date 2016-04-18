// kk.c

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ITERS 25000
#define SIZE 100
#define MAX 1000000000000

// from c++reference
int compare (const void * a, const void * b)
{
  	return ( *(int*)b - *(int*)a );
}

// from http://stackoverflow.com/questions/7920860/how-to-generate-large-random-numbers-c
uint64_t gen() 
{
	uint64_t num;
	num = rand();
	return ((num << 32) + rand()) % MAX;
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
	// sort in reverse order
	uint64_t * diffArray = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
	memcpy(diffArray, array, SIZE * sizeof(uint64_t));
	qsort(diffArray, SIZE, sizeof(uint64_t), compare);

	// recursively find differences
	while (true)
	{
		for (unsigned int i = 0; i < SIZE - 1; i += 2)
		{
			if (diffArray[i] == 0)  break;	
			diffArray[i] = diffArray[i] - diffArray[i + 1];
			diffArray[i + 1] = 0;
		}
		qsort(diffArray, SIZE, sizeof(uint64_t), compare);
		if (diffArray[1] == 0)  break;
	}

	// return best
	uint64_t best = diffArray[0];
	free(diffArray);
	return best;
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
