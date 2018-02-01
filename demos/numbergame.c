/* numbergame.c: The number game of TravorOS v0.4-r1's kernel */.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int _cmp(int x,int y){
	if(x>y){
		return 2;
	}else if(x<y){
		return 0;
	}
	return 1;
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
