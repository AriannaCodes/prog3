// header.h

// algorithms
uint64_t kk(const uint64_t array[]);
uint64_t rrandom(const uint64_t array[]);
uint64_t hc(const uint64_t array[]);
uint64_t sa(const uint64_t array[]);

// helpers
unsigned int binary(uint64_t value, uint64_t array[], unsigned int lower, unsigned int upper);
int compare(void const*a, void const*b);
uint64_t gen();
uint64_t* randArray();
bool sorted(uint64_t * array);
uint64_t t(unsigned int iter);