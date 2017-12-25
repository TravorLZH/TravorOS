#include <stdio.h>

int main(void){
	char* vidmem=(char*)0xb8000;
	*vidmem='X';
	*(vidmem+1)=0x0F;
	return 0;
}
