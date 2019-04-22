#include <stdio.h>
#include <stdlib.h>


#define PWLEN 16
char pw[16] = "paddingbreaksxor";
//char pw[16] = "cantfigureoutxor";

int main(void){

	int i;
	int c;
	for(i = 0; (c = fgetc(stdin)) != EOF; i= (i+1)%PWLEN){
		fputc(c ^ pw[i], stdout);
	}

	for(; i; i= (i+1)%PWLEN){
		fputc(0 ^ pw[i] , stdout);
	}

	return 0;


}
