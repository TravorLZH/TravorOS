#include <kernel/dbg.h>
#include <stdio.h>

void __assert(const char* msg,const char* file, int line){
	kprint("Panic: Assertion Failed: %s at %s, line %d",msg,file,line);
	while(1);
}
