/* testing.c -- tests the accuracy of our
                random number generating function */

#define MAX 1000000000000
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

uint64_t gen() 
{
	uint64_t num;
	int a = (rand() % 2 == 0) ? 1 : 0;
	int b = (rand() % 2 == 0) ? 1 : 0;
	num = 2 * rand() + a;
	return (((num << 32) + 2*rand() + b) % MAX) + 1;
}

int main(int argc, char * argv[])
{
	time_t ti = time(NULL);
	srand((unsigned) time(&ti));

	for (int i = 0; i < 100000; i++)
		printf("%llu\n", gen());
}