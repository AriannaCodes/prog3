// kk.cpp -- Abby Lyons & Arianna Benson

#include <list>
#include "helpers.h"
#include "kk.h"

#define INSTANCES 50

struct Node
{
    uint64_t num;
    int index;

    Node(uint64_t n, int i) : num(n), index(i)
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
	uint64_t * arr;
	// seed random number generator
	time_t ti = time(NULL);
	srand((unsigned) time(&ti));

	if (argc == 2)
	{
		printf("Inputfile given! Reading in... \n");

		arr = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
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
		printf("----------\n");
	}
	else if (argc == 1)
	{
		double bkk = 0.0;
		double brr = 0.0;
		double bhc = 0.0;
		double bsa = 0.0;
		double brrr = 0.0;
		double bhcr = 0.0;
		double bsar = 0.0;

		printf("No inputfile given! Constructing random arrays...\n");
		for (unsigned int instances = 0; instances < INSTANCES; ++instances)
		{
			// make random array
			uint64_t * arr = randArray();

			bkk += kk(arr) / INSTANCES;
			brr += rr(arr, false) / INSTANCES;
			bhc += hc(arr, false) / INSTANCES;
			bsa += sa(arr, false) / INSTANCES;
			brrr += rr(arr, true) / INSTANCES;
			bhcr += hc(arr, true) / INSTANCES;
			bsar += sa(arr, true) / INSTANCES;
			printf("Round %d done\n", instances);

			printf("KK: %llu\n", kk(arr));
			printf("RR: %llu\n", rr(arr, false));
			printf("HC: %llu\n", hc(arr, false));
			printf("SA: %llu\n", sa(arr, false));

			printf("Pre-partitioning!\n");
			printf("RR: %llu\n", rr(arr, true));
			printf("HC: %llu\n", hc(arr, true));
			printf("SA: %llu\n", sa(arr, true));

			free(arr);
		}
		printf("%f\n%f\n%f\n%f\n%f\n%f\n%f\n", bkk, brr, bhc, bsa, brrr, bhcr, bsar);
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
	int64_t min = INT64_MAX;

	// store partitioning
	int* part;

	// make a copy of original array for modification
	uint64_t* copy = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
	
	// get random assignment
	for (unsigned int i = 0; i < ITERS; ++i)
	{
		int64_t sum = 0;
		// if pp, then preparition our array
		if (pp)
		{
			memset(copy, 0, SIZE * sizeof(uint64_t));
			part = prepart(array);
			for (int i = 0; i < SIZE; i++)
		    {
		        copy[part[i]] += array[i];
		    }
		    sum = kk(copy);
		    free(part);
		}
		else
		{
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
			sum = llabs(sum);
		}
		if (sum < min)
		{
			min = sum;
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
	int64_t sum = 0;

	// array to store what's in set
	bool set[SIZE];

	// make a copy of original array for modification
	uint64_t* copy = (uint64_t *) malloc(SIZE * sizeof(uint64_t));

	// if we're prepartitioning
	if (pp)
	{
		memset(copy, 0, SIZE * sizeof(uint64_t));
		int* part = prepart(array);
		for (int i = 0; i < SIZE; i++)
	    {
	        copy[part[i]] += array[i];
	    }
	    min = kk(copy);
	    
	    // iterate
	    for (unsigned int i = 0; i < ITERS; ++i)
		{
			// randomly gen two places
			int a = rand() % SIZE;
			
			int prev_part = -1;
			
			// ensure b != a
			int b;
			while(true)
			{
				b = rand() % SIZE;
				if (part[a] != b)
				{
					prev_part = part[a];
					part[a] = b;
					break;
				}
			}
			
			memset(copy, 0, SIZE * sizeof(uint64_t));
			for (int i = 0; i < SIZE; i++)
		    {
		        copy[part[i]] += array[i];
		    }
		    sum = kk(copy);
			
			// see if it got better
			sum = kk(copy);
			if (sum < min)
			{
				min = sum;
			}
			// undo changes
			else
			{
				part[a] = prev_part;
			}
		}
		free(part);
	}
	// if we're not prepartitioning
	else
	{
		// assign elements of array
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
		min = (sum < 0) ? (-1 * sum) : (sum);

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
			set[a] = !set[a];
			bool swapped = false;
			if (rand() % 2 == 0)
			{
				swapped = true;
				set[b] = !set[b];
			}
			
			// calculate new residue
			sum = 0;
			for (int j = 0; j < SIZE; ++j)
			{
				set[j] ? (sum += array[j]) : (sum -= array[j]);
			}
			sum = (sum < 0) ? (-1 * sum) : (sum);

			// see if we got better
			if (sum < min)
			{
				min = sum;
			}
			
			// if not better, go to the previous solution
			else
			{
				set[a] = !set[a];
				if (swapped)  set[b] = !set[b];
			}
		}
	}
	free(copy);
	return min;
}

// SIMULATED ANNEALING
uint64_t sa(const uint64_t array[], bool pp)
{
	assert(array != NULL);
	int64_t sum = 0;
	uint64_t best_min = UINT64_MAX;
	uint64_t min = UINT64_MAX;

	// array to store what's in set
	bool set[SIZE];

	// make a copy of original array for modification
	uint64_t* copy = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
	memcpy(copy, array, SIZE * sizeof(uint64_t));	

	// if we're prepartitioning
	if (pp)
	{
		memset(copy, 0, SIZE * sizeof(uint64_t));
		int* part = prepart(array);
		for (int i = 0; i < SIZE; i++)
	    {
	        copy[part[i]] += array[i];
	    }
	    best_min = kk(copy);
	    min = best_min;
	    
	    // iterate
	    for (unsigned int i = 0; i < ITERS; ++i)
		{
			// randomly gen two places
			int a = rand() % SIZE;
			
			int prev_part = -1;
			
			// ensure b != a
			int b;
			while(true)
			{
				b = rand() % SIZE;
				if (part[a] != b)
				{
					prev_part = part[a];
					part[a] = b;
					break;
				}
			}
			
			memset(copy, 0, SIZE * sizeof(uint64_t));
			for (int i = 0; i < SIZE; i++)
		    {
		        copy[part[i]] += array[i];
		    }
		    sum = kk(copy);
		    
		    // see if we got better
			if (sum < best_min)
			{
				best_min = sum;
				min = sum;
			}
			// if not, maybe keep the result anyway
			else if (drand48() <= exp(-1 * (sum - min)) / t(i))
			{
				min = sum;
			}
			// if all else fails, undo calculations
			else
			{
				part[a] = prev_part;
			}
		}
		free(part);
	}
	else
	{
		// assign elements of array
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
		best_min = (sum < 0) ? (-1 * sum) : (sum);
		min = best_min;

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
			set[a] = !set[a];
			bool swapped = false;
			if (rand() % 2 == 0)
			{
				swapped = true;
				set[b] = !set[b];
			}
			
			// calculate new residue
			sum = 0;
			for (int j = 0; j < SIZE; ++j)
			{
				set[j] ? (sum += array[j]) : (sum -= array[j]);
			}
			sum = (sum < 0) ? (-1 * sum) : (sum);

			// see if we got better
			if (sum < best_min)
			{
				best_min = sum;
				min = sum;
			}
			// if not, maybe keep the result anyway
			else if (drand48() <= exp(-1 * (sum - min)) / t(i))
			{
				min = sum;
			}
			// if all else fails, undo calculations
			else
			{
				set[a] = !set[a];
				if (swapped)  set[b] = !set[b];
			}
		}
	}
	free(copy);
	return best_min;
}