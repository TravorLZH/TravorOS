#include <asm/shutdown.h>

void shutdown(){
	outb(0xF4,0);
}
