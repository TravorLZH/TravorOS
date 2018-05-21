#include <fibonacci.h>

int get_fibonacci(size_t index)
{
	int a=1;
	int b=1;
	int tmp=a;
	index-=2;
	if(index<=0)return 1;
	while(index--){
		tmp=a;
		a=b;
		b+=tmp;
	}
	return b;
}

