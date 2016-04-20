// helpers.cpp

#include "helpers.h"

// compares two values
int compare(void const *a, void const *b)
{
  	uint64_t * const A = (uint64_t *) a;
  	uint64_t * const B = (uint64_t *) b;
  	{
    	uint64_t const a = *A;
    	uint64_t const b = *B;
    	return (a > b) ? -1 : (a < b);
  	}
}

// generates a random number between 0 and MAX
// (from: http://stackoverflow.com/questions/7920860/
//        how-to-generate-large-random-numbers-c)
uint64_t gen() 
{
	uint64_t num;
	num = rand();
	return (((num << 32) + rand()) % MAX) + 1;
}

int* prepart(const uint64_t arr[])
{
    int * set = (int *) malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++)
    {
        set[i] = rand() % SIZE;
    }
    return set;
}

// generates a random array of size SIZE 
uint64_t* randArray()
{
	uint64_t* arr = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = gen();
	}
	return arr;
}

uint64_t t(unsigned int iter)
{
    return (uint64_t) pow(10, 10) * pow(0.8, (int) iter / 300);
}
