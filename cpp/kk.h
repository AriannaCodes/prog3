// kk.h

#define ITERS 25000

#include <assert.h>
#include <queue>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

bool* kk_arr(const uint64_t array[]);
uint64_t kk(const uint64_t array[]);
uint64_t rr(const uint64_t array[], bool pp);
uint64_t hc(const uint64_t array[], bool pp);
uint64_t sa(const uint64_t array[]);
void getResidue(const uint64_t array[], bool* set);
int dfs(bool* set, std::list<int> *edges, bool* visited, int j, bool cur, int count);