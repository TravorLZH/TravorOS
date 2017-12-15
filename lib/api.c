#include "api.h"

int _api_putchar(char* addr,char c,char attr){
	if(c==0){
		return 1;
	}
	*addr=c;
	addr++;
	*addr=attr;
	return 0;
}