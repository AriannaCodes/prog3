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
	// seed random number generator
	time_t t;
	t = time(NULL);
	srand((unsigned) time(&t));

	// create array
	uint64_t* arr;

	if (argc == 2)
	{
		uint64_t* arr = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
		
		printf("Inputfile given! Reading in... \n");

		FILE* file;
		char* line = NULL;
		size_t len = 0;
		ssize_t read;

		file = fopen(argv[1], "r");

		int i = 0;
		while((read = getline(&line, &len, file)) != -1)
		{
			// remove newline
			size_t ln = strlen(line) - 1;
			if (*line && line[ln] == '\n') 
			    line[ln] = '\0';

			arr[i] = atoi(line);
			printf("%s\n", line);
			printf("i is %i, arr[i] is %llu...\n", i, arr[i]);

			i++;
		}

		printf("HEY");

		fclose(file);
	}
	else if (argc == 1)
	{
		printf("No inputfile given! Constructing random array...\n");

		// make random array
		time_t t;
		t = time(NULL);
		srand((unsigned) time(&t));

		uint64_t* arr = randArray();

		printf("Karmarkar-Karp: %llu\n", kk(arr));
		printf("Repeated random: %llu\n", rrandom(arr));
	}
	else
	{
		printf("Invalid input\n");
		return 0;
	}

	printf("Hill-climbing: %llu\n", hc(arr));
	printf("Simulated annealing: %llu\n", sa(arr));
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
	uint64_t min = UINT64_MAX;
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		int64_t sum = 0;
		// randomly assign every element of the array
		for (int i = 0; i < SIZE; i++)
		{
			if (rand() % 2 == 0)
			{
				sum += array[i];
			}
			else
			{
				sum -= array[i];
			}
		}
		uint64_t abs_sum = llabs(sum);
		if (abs_sum < min)
		{
			min = abs_sum;
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
