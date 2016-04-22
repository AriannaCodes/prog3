// helpers.cpp

#include "helpers.h"
#include <list>

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


// performs depth first search to get partitioning
int dfs(bool* set, std::list<int> *edges, bool* visited,
         int j, bool cur, int count)
{
    if (!visited[j])
    {
      // increment total count
      count++;

      // set our current elt to true
      set[j] = cur;
      visited[j] = true;

      // look through links
      std::list<int>::iterator i;
      std::list<int> e = edges[j];
      for (i = e.begin(); i != e.end(); ++i)
      {
          if (!visited[*i])
          {
              count += dfs(set, edges, visited, *i, !cur, 0);
          }
      }
    }
    printf("visited %i\n", j);
    printf("count %i\n", count);
    return count;
}
