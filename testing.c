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
	num = rand();
	return (((num << 32) + rand()) % MAX) + 1;
}

int main(int argc, char * argv[])
{
	time_t ti = time(NULL);
	srand((unsigned) time(&ti));

	printf("1000000000000\n");
	for (int i = 0; i < 20; i++)
		printf("%llu \n", gen());
}