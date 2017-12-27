#include <screen.h>

void _sleep(long long sec){
	sec*=10000;
	while(sec--);
}

int main(void){
	print_at("KERNEL\n",-1,-1,0x07);
	int i=1;
	for(;;i++){
		_sleep(100);
		print_char(' ',-1,-1,(i%16)*16);
	}
	return 0;
}
