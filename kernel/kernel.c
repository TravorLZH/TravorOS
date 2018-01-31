/* 
* TravorOS: A simple OS running on Intel x86 Architecture
* Copyright (C) 2017  Travor Liu
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/* kernel.c: The core part of the OS kernel (i.e. The heart of the OS) */
#include <misc.h>
#include <def.h>
#include <string.h>
#include <random.h>
#include <kbd.h>
#include <stdio.h>
#define	COLOR	0x70

void _sleep(long long sec){
	sec*=10000;
	while(sec--);
}

int main(void){
	char cmdline[3];
	int num;
	unsigned long number;
	char result;
	while(1){
		number=rand()%100;
		printf("\nI'm thinking of a number between 0 and 100, try to guess what it is: ");
		while(1){
			memset(cmdline,0,3);
			gets(cmdline);
			num=atoi(cmdline);
			result=_cmp(num,number);
			if(result==2){printf("%d is Too large! ",num);continue;}
			if(result==0){printf("%d is Too small! ",num);continue;}
			if(result==1){break;}
			printf("Oh fuck!\n");
		}
		printf("Oh! you guess it right! It's %d\n",num);
	}
	printf("Oh fuck! How do you get here?\n");
	return 0;
}
