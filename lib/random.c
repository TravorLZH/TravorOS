// Taken from C standard document */
/* random.c: Simple implementation of random algorithm */
#include <random.h>

static unsigned long next=1;

int rand(void){
	next=next*1103515245 + 12345;
	int a=3;
	while(a--){
		int val=(unsigned int)(next / 65536) % 32768;
		srand(val);
		val=val*1103515245+12345;
	}
}

void srand(unsigned int seed){
	next=seed;
}

