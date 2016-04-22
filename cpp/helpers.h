// helpers.h

#define MAX 10
#define SIZE 5

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <list>

int compare(void const*a, void const*b);
uint64_t gen();
int* prepart(const uint64_t arr[]);
uint64_t* randArray();
uint64_t t(unsigned int iter);
int dfs(bool* set, std::list<int> *edges, bool* visited, int j, bool cur, int count);