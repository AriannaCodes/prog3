// kk.cpp -- Abby Lyons & Arianna Benson

#include <list>
#include "helpers.h"
#include "kk.h"

#define INSTANCES 50

int main(int argc, char * argv[])
{
	// seed random number generator
	time_t ti = time(NULL);
	srand((unsigned) time(&ti));

	if (argc == 2)
	{
		printf("Inputfile given! Reading in... \n");

		uint64_t * arr = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
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
		printf("----------\n");
	}
	else if (argc == 1)
	{
		double res_kk_total = 0.0;
		double res_rr_total = 0.0;
		double res_hc_total = 0.0;
		double res_sa_total = 0.0;
		double res_rrp_total = 0.0;
		double res_hcp_total = 0.0;
		double res_sap_total = 0.0;

		printf("No inputfile given! Constructing random arrays...\n");
		for (unsigned int instances = 0; instances < INSTANCES; ++instances)
		{
			// make random array
			uint64_t * arr = randArray();

			// set totals
			res_kk_total += kk(arr);
			res_rr_total += rr(arr, false);
			res_hc_total += hc(arr, false);
			res_sa_total += sa(arr, false);
			res_rrp_total += rr(arr, true);
			res_hcp_total += hc(arr, true);
			res_sap_total += sa(arr, true);

			// clean up
			printf("Round %d done\n", instances);
			free(arr);
		}

		// we're done!
		printf("Karmarkar-Karp: %f\n", res_kk_total / INSTANCES);
		printf("Repeated random: %f\n", res_rr_total / INSTANCES);
		printf("Hill-climbing: %f\n", res_hc_total / INSTANCES);
		printf("Simulated annealing: %f\n", res_sa_total / INSTANCES);
		printf("Repeated random w/ prepartitioning: %f\n", res_rrp_total / INSTANCES);
		printf("Hill-climbing w/ prepartitioning: %f\n", res_hcp_total / INSTANCES);
		printf("Simulated annealing w/ prepartitioning: %f\n", res_sap_total / INSTANCES);
		printf("----------\n");
	}
	else
	{
		printf("Invalid input\n");
		return 0;
	}
}

// karmarkar karp
uint64_t kk(const uint64_t array[])
{
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

// REPEATED RANDOM
// if pp = true, repeatedly prepartitions and runs kk on array
uint64_t rr(const uint64_t array[], bool pp)
{
	// initialize min
	int64_t min = INT64_MAX;

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
			int * part = prepart(array);
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

// HILL-CLIMBING
// if pp = true, prepartitions, runs kk, then iterates
uint64_t hc(const uint64_t array[], bool pp)
{
	int64_t min = INT64_MAX;
	int64_t sum = 0;

	// if we're prepartitioning
	if (pp)
	{
		// make a copy of original array for modification
		uint64_t* copy = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
		memset(copy, 0, SIZE * sizeof(uint64_t));

		// start prepartitioning
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
		free(copy);
	}
	// if we're not prepartitioning
	else
	{
		// array to store what's in the set
		bool set[SIZE];

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
	return min;
}

// SIMULATED ANNEALING
uint64_t sa(const uint64_t array[], bool pp)
{
	int64_t sum = 0;
	uint64_t best_min = UINT64_MAX;
	uint64_t min = UINT64_MAX;

	// array to store what's in set
	bool set[SIZE];

	// if we're prepartitioning
	if (pp)
	{
		uint64_t * copy = (uint64_t *) malloc(SIZE * sizeof(uint64_t));
		memset(copy, 0, SIZE * sizeof(uint64_t));
		int * part = prepart(array);
		for (int i = 0; i < SIZE; i++)
	    {
	        copy[part[i]] += array[i];
	    }
	    best_min = kk(copy);
	    min = best_min;
	    
	    // iterate through neighbors
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
		free(copy);
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
	return best_min;
}