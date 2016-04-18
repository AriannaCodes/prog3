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
unsigned int kk(uint64_t array[]);
unsigned int rrandom(uint64_t array[]);
unsigned int hc(uint64_t array[]);
unsigned int sa(uint64_t array[]);
int compare(const void * a, const void * b);

// from c++reference
int compare(const void * a, const void * b)
{
  	return ( *(int*)b - *(int*)a );
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
		arr = randArray();
	}
	else
	{
		printf("Invalid input\n");
		return 0;
	}

	printf("Karmarkar-Karp: %i\n", kk(arr));
	printf("Repeated random: %i\n", rrandom(arr));
	printf("Hill-climbing: %i\n", hc(arr));
	printf("Simulated annealing: %i\n", sa(arr));
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

// repeated random
unsigned int rrandom(uint64_t array[])
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

// hill-climbing
unsigned int hc(uint64_t array[])
{
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		
	}
	return 0;
}

// simulated annealing
unsigned int sa(uint64_t array[])
{
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		
	}
	return 0;
}
