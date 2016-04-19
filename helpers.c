// performs binary search on an array
unsigned int binary(uint64_t value, uint64_t array[],
                    unsigned int lower, unsigned int upper)
{
    // calculate midpoint
    unsigned int mid = lower + ((upper - lower) / 2);
    
    // check if done
    if (mid == SIZE - 1)
    {
    	return mid;
    }
    if (array[mid] >= value && array[mid + 1] < value)
    {
        return mid;
    }
    
    // we're not done! continue
    if (array[mid] < value)
    {
        return binary(value, array, lower, mid - 1);
    }
    return binary(value, array, mid + 1, upper);    
}

// compares two values
int compare(void const *a, void const *b)
{
  	uint64_t const*const A = a;
  	uint64_t const*const B = b;
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
	return ((num << 32) + rand()) % MAX;
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
