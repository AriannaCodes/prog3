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
void getResidue(const uint64_t array[], bool* set);
int* prepart(const uint64_t arr[]);
uint64_t* randArray();
uint64_t t(unsigned int iter);

struct Node
{
    uint64_t num;
    int index;

    Node(uint64_t n, int i) : num(n), index(i)
    {
    	// nothing to do here
    }

    bool operator<(const struct Node& other) const
    {
        return num < other.num;
    }
};