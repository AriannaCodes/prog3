// helpers.h

#define MAX 1000000000000
#define SIZE 100

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>

int compare(void const*a, void const*b);
uint64_t gen();
int* prepart(const uint64_t arr[]);
uint64_t* randArray();
uint64_t t(unsigned int iter);
