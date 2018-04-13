/* test.c: Various Testing of Hardware for my kernel */
#include <kernel/test.h>
#include <stdio.h>

// This function reads string from terminal
void kbd_test(void)
{
	while(1){
		getchar();
	}
}
