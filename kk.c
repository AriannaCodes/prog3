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

uint64_t gen();
uint64_t* randArray();
uint64_t kk(uint64_t array[]);
uint64_t rrandom(uint64_t array[]);
uint64_t hc(uint64_t array[]);
uint64_t sa(uint64_t array[]);
int compare(const void * a, const void * b);
unsigned int binary(uint64_t value, uint64_t array[], unsigned int lower, unsigned int upper);

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
		printf("No inputfile given! Constructing random array...\n");

		// make random array
		time_t t;
		t = time(NULL);
		srand((unsigned) time(&t));
		uint64_t* arr = randArray();

		// run algorithms
		printf("Repeated random: %llu\n", rrandom(arr));
		printf("Hill-climbing: %llu\n", hc(arr));
		printf("Simulated annealing: %llu\n", sa(arr));
	}
	else
	{
		printf("Invalid input\n");
	}
}

// Karmarkar-Karp
uint64_t kk(uint64_t array[])
{
	// sort in reverse order
	uint64_t * diffArray = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
	memcpy(diffArray, array, SIZE * sizeof(uint64_t));
	qsort(diffArray, SIZE, sizeof(uint64_t), compare);

	// recursively find differences
	while (true)
	{
		if (diffArray[1] == 0)  break;
		diffArray[0] -= diffArray[1];
		diffArray[1] = 0;
		// binary search
		unsigned int index_before = binary(diffArray[0], diffArray, 1, SIZE);
		
		// shift over
		uint64_t temp = diffArray[0];
		for (unsigned int i = 2; i <= index_before; ++i)
		{
			diffArray[i - 2] = diffArray[i];
		}

		// insert
		diffArray[index_before - 1] = temp;
		diffArray[index_before] = 0;
	}

	// return best
	uint64_t best = diffArray[0];
	free(diffArray);
	return best;
}

// Repeated random
uint64_t rrandom(uint64_t array[])
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
uint64_t hc(uint64_t array[])
{
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		
	}
	return 0;
}

// Simulated annealing
uint64_t sa(uint64_t array[])
{
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		
	}
	return 0;
}

unsigned int binary(uint64_t value, uint64_t array[], unsigned int lower, unsigned int upper)
{
    // calculate mid
    unsigned int mid = lower + ((upper - lower) / 2);
    
    // are we done?
    if (mid == upper)
    {
    	return mid;
    }
    if (array[mid] <= value && array[mid + 1] > value)
    {
        return mid;
    }
    
    // we're not done
    if (array[mid] > value)
    {
        return binary(value, array, lower, mid - 1);
    }
    else
    {
        return binary(value, array, mid + 1, upper);
    }
}

// from c++reference
int compare(const void * a, const void * b)
{
  	return ((*(uint64_t*)b - *(uint64_t*)a > 0) ? (int) 1 : (int) -1);
}

// from http://stackoverflow.com/questions/7920860/
// how-to-generate-large-random-numbers-c
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
