// kk.cpp -- Abby Lyons & Arianna Benson

#include "helpers.h"
#include "kk.h"

struct Node
{
    uint64_t num;
    int index;

    Node(uint64_t n, int i) 
    : num(n), index(i)
    {
    }

    bool operator<(const struct Node& other) const
    {
        //Your priority logic goes here
        return num < other.num;
    }
};

int main(int argc, char * argv[])
{
	// seed random number generator
	time_t ti = time(NULL);
	srand((unsigned) time(&ti));

	// create arrays
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
		getResidue(arr, kk_arr(arr));
		free(arr);

		fclose(file);
	}
	else if (argc == 1)
	{
		printf("No inputfile given! Constructing random arrays...\n");
		for (unsigned int instances = 0; instances < 1; ++instances)
		{
			// make random array
			arr = randArray();

			printf("KK: %llu\n", kk(arr));
			printf("RR: %llu\n", rr(arr, false));
			printf("HC: %llu\n", hc(arr, false));
			printf("SA: %llu\n", sa(arr));

			getResidue(arr, kk_arr(arr));
			return 0;

			printf("Pre-partitioning!\n");
			printf("RR: %llu\n", rr(arr, true));
			printf("HC: %llu\n", hc(arr, true));

			free(arr);
		}
	}
	else
	{
		printf("Invalid input\n");
		return 0;
	}

}

uint64_t kk(const uint64_t array[])
{
	// priority queue implementation
	std::priority_queue<uint64_t> q;
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		q.push(array[i]);
	}
	q.push(0);
	q.push(0);
	while (true)
	{
		uint64_t a = q.top();
		q.pop();
		uint64_t b = q.top();
		q.pop();
		if (b == 0)  return a;
		q.push(a - b);
	}
}

// Karmarkar-Karp
bool* kk_arr(const uint64_t array[])
{
	// store what's in our set
	bool* set = (bool *) malloc(SIZE * sizeof(bool));
	int64_t x = 0;
	int64_t y = 0;

	// priority queue implementation
	std::priority_queue<Node> q;
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		q.push(Node(array[i], i));
	}
	q.push(Node(0, -1));
	q.push(Node(0, -1));
	while (true)
	{
		Node a = q.top();
		q.pop();
		Node b = q.top();
		q.pop();

		if (y < x)
		{
			if (a.index != -1 && b.index != -1)
			{
				set[a.index] = false;
				y = y + a.num;
				set[b.index] = true;
				x = x + b.num;
			}
			else if (a.index != -1)
			{
				set[a.index] = false;
				y = y + a.num;
			}
			else if (b.index != -1)
			{
				set[b.index] = false;
				y = y + b.num;
			}
		}
		else
		{
			// put bigger elt in smaller set
			if (a.index != -1 && b.index != -1)
			{
				set[a.index] = true;
				x = x + a.num;
				set[b.index] = false;
				y = y + b.num;
			}
			else if (a.index != -1)
			{
				set[a.index] = true;
				x = x + a.num;
			}
			else if (b.index != -1)
			{
				set[b.index] = true;
				x = x + b.num;
			}

			/*
			// put smaller elt in bigger set
			if (b.index != -1)
			{
				set[b.index] = true;
				y = y + b.num;
				printf("small goes into y\n");
			}*/
		}

		if (b.num == 0) 
	    {
	    	printf("X: %lli\nY: %lli\nDiff:%lli\n", x, y, x - y);
	    	return set;
	    }
		q.push(Node(a.num - b.num, -1));
	}
}

// REPEATED RANDOM
// if pp = true, repeatedly prepartitions and runs kk on array
uint64_t rr(const uint64_t array[], bool pp)
{
	// declare sums and min
	uint64_t min = UINT64_MAX;
	int64_t sum = 0;
	uint64_t abs_sum;

	// store partitioning
	int* part;
	uint64_t * full;

	// make a copy of original array for modification
	uint64_t* copy = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
	memcpy(copy, array, SIZE * sizeof(uint64_t));	
	
	// get random assignment
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		// if pp, then preparition our array
		if (pp)
		{
			part = prepart(array);
			full = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
			for (int i = 0; i < SIZE; i++)
		    {
		        copy[part[i]] += array[i];
		    }
		    abs_sum = kk(copy);
		}
		else
		{
			// randomly assign every element of the array
			for (int i = 0; i < SIZE; i++)
			{
				if (rand() % 2 == 0)
				{
					sum += copy[i];
				}
				else
				{
					sum -= copy[i];
				}
			}
			abs_sum = llabs(sum);
		}
		if (abs_sum < min)
		{
			min = abs_sum;
		}
	}
	return min;
}

void getResidue(const uint64_t array[], bool* set)
{
	int64_t sum = 0;

	// randomly assign every element of the array
	for (int i = 0; i < SIZE; i++)
	{
		if (set[i])
		{
			sum = sum + array[i];
		}
		else
		{
			sum = sum - array[i];
		}
	}

	printf("%lli\n", sum);
}

// HILL-CLIMBING
// if pp = true, prepartitions, runs kk, then iterates
uint64_t hc(const uint64_t array[], bool pp)
{
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

// SIMULATED ANNEALING
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