// kk.cpp -- Abby Lyons & Arianna Benson

#define ITERS 25000
#define SIZE 100
#define MAX 1000000000000

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "header.h"
#include "helpers.cpp"

int main(int argc, char * argv[])
{
	// seed random number generator
	time_t ti = time(NULL);
	srand((unsigned) time(&ti));

	// create array
	uint64_t* arr;

	if (argc == 2)
	{
		arr = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
		
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
			i++;
		}
		printf("Karmarkar-Karp: %llu\n", kk(arr));
		free(arr);

		fclose(file);
	}
	else if (argc == 1)
	{
		printf("No inputfile given! Constructing random arrays...\n");
		for (unsigned int instances = 0; instances < 50; ++instances)
		{
			// make random array
			arr = randArray();

			printf("%llu,", kk(arr));
			printf("%llu,", rrandom(arr));
			printf("%llu,", hc(arr));
			printf("%llu\n", sa(arr));
			free(arr);
		}
	}
	else
	{
		printf("Invalid input\n");
		return 0;
	}

}

// Karmarkar-Karp
uint64_t kk(const uint64_t array[])
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
		if (diffArray[0] < diffArray[2])
		{
			unsigned int index_before = binary(diffArray[0], diffArray, 2, SIZE - 1);
			// shift over
			uint64_t temp = diffArray[0];
			for (unsigned int i = 2; i <= index_before; ++i)
			{
				diffArray[i - 2] = diffArray[i];
			}
			diffArray[index_before - 1] = temp;
			for (unsigned int i = index_before; i < SIZE - 1; ++i)
			{
				diffArray[i] = diffArray[i + 1];
			}
			diffArray[SIZE - 1] = 0;
		}
		else
		{
			for (unsigned int i = 1; i < SIZE - 1; ++i)
			{
				diffArray[i] = diffArray[i + 1];
			}
			diffArray[SIZE - 1] = 0;
		}
	}

	// return best
	uint64_t best = diffArray[0];
	free(diffArray);
	return best;
}

// Repeated random
uint64_t rrandom(const uint64_t array[])
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
uint64_t hc(const uint64_t array[])
{
	assert(array != NULL);
	int64_t min = INT64_MAX;
	uint64_t abs_min = INT64_MAX;
	int64_t sum = 0;
	uint64_t abs_sum = 0;

	// array to store what's in set
	bool set[SIZE];

	// randomly assign every element of the array
	for (int i = 0; i < SIZE; i++)
	{
		if (rand() % 2 == 0)
		{
			sum = sum + array[i];
			set[i] = true;
		}
		else
		{
			sum = sum - array[i];
			set[i] = false;
		}
	}

	min = sum;
	abs_min = (min < 0) ? (-1 * min) : (min);

	// iterate through neighbours
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		// randomly gen two places
		int a = rand() % SIZE;
		// ensure b != a
		int b;
		do {
			b = rand() % SIZE;
		} while (b == a);

		// swap (with prob 1/2)
		sum = min;
		if (rand() % 2 == 0)
		{
			set[a] = !set[a];
			sum = (set[a]) ? (sum + 2*array[a]) : (sum - 2*array[a]);
		}
		if (rand() % 2 == 0)
		{
			set[b] = !set[b];
			sum = (set[b]) ? (sum + 2*array[b]) : (sum - 2*array[b]);
		}

		// get our new absolute sum
		abs_sum = (sum < 0) ? (-1 * sum) : (sum);

		// see if we got better
		if (abs_sum < abs_min)
		{
			min = sum;
			abs_min = abs_sum;
		}
	}
	return abs_min;
}

// Simulated annealing
uint64_t sa(const uint64_t array[])
{
	assert(array != NULL);
	int64_t best_min = INT64_MAX;
	uint64_t best_abs_min = INT64_MAX;
	int64_t sum = 0;
	uint64_t abs_sum = 0;

	// array to store what's in set
	bool set[SIZE];

	// randomly assign every element of the array
	for (int i = 0; i < SIZE; i++)
	{
		if (rand() % 2 == 0)
		{
			sum = sum + array[i];
			set[i] = true;
		}
		else
		{
			sum = sum - array[i];
			set[i] = false;
		}
	}

	best_min = sum;
	best_abs_min = (best_min < 0) ? (-1 * best_min) : (best_min);
	int64_t init_min = best_min;
	uint64_t init_abs_min = best_abs_min;

	// iterate through neighbours
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		// randomly gen two places
		int a = rand() % SIZE;
		// ensure b != a
		int b;
		do {
			b = rand() % SIZE;
		} while (b == a);

		// swap (with prob 1/2)
		sum = init_min;
		if (rand() % 2 == 0)
		{
			set[a] = !set[a];
			sum = (set[a]) ? (sum + 2*array[a]) : (sum - 2*array[a]);
		}
		if (rand() % 2 == 0)
		{
			set[b] = !set[b];
			sum = (set[b]) ? (sum + 2*array[b]) : (sum - 2*array[b]);
		}

		// get our new absolute sum
		abs_sum = (sum < 0) ? (-1 * sum) : (sum);

		// see if we got better
		if (abs_sum < init_abs_min)
		{
			init_min = sum;
			init_abs_min = abs_sum;
		}
		// if not, maybe keep the result anyway
		else if (drand48() <= exp(-1 * (abs_sum - init_abs_min)) / t(i))
		{
			init_min = sum;
			init_abs_min = abs_sum;
		}
		// record the best value
		if (init_abs_min < best_abs_min)
		{
			best_min = init_min;
			best_abs_min = init_abs_min;
		}
	}
	return best_abs_min;
}
