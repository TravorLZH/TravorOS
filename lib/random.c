// Taken from C standard document */
/* random.c: Simple implementation of random algorithm */
#include <random.h>
#include <fibonacci.h>

static unsigned long next=0xBABA;

unsigned long rand(void){
	next=next*get_fibonacci(next)%RAND_MAX+12345;
	return (next%RAND_MAX);
}

void srand(unsigned int seed){
	next=seed;
}

