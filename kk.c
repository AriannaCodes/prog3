// kk.c

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITERS 25000
#define SIZE 100
#define MAX 1000000000000

uint64_t gen();
uint64_t* randArray();
unsigned int kk(uint64_t array[]);
unsigned int rrandom(uint64_t array[]);
unsigned int hc(uint64_t array[]);
unsigned int sa(uint64_t array[]);

// from http://stackoverflow.com/questions/7920860/how-to-generate-large-random-numbers-c
uint64_t gen() 
{
	uint64_t num;
	num = rand();
	return ((num << 32) + rand()) % MAX;
}

// generate a random array of SIZE 
uint64_t* randArray()
{
	uint64_t* arr = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = gen();
	}
	return arr;
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
		printf("No inputfile given! Constructing random array...\n");
		uint64_t* arr = randArray();
		printf("Repeated random: %i\n", rrandom(arr));
		printf("Hill-climbing: %i\n", hc(arr));
		printf("Simulated annealing: %i\n", sa(arr));
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
	uint64_t min = MAX;
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		uint64_t sum = 0;
		// randomly assign every element of the array
		for (int i = 0; i < 100; i++)
		{
			if (rand() % 2 == 1)
			{
				sum += array[i];
			}
			else
			{
				sum -= array[i];
			}
		}
		if (sum < min)
		{
			min = sum;
		}
	}
	return min;
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
