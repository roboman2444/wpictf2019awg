#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

char * durch = "wpi{";
char * lurch = "warbleglarblesomejunkwpi{What_do_you_mean_I_SEE_AHH_SKI}0x13376969";


char * buf = 0;
size_t bsize = 0;
size_t bplace = 0;

int pushc(char c){
	if(bplace <= bsize){
		bsize = bplace + 128;
		buf = realloc(buf, bsize);
	}
	buf[bplace++] = c;
}
void dump(void){
	int i;
	for(i = 0; i < bplace; i++){
		putc(buf[i], stdout);
	}
	bplace = 0;
}

char *dc;
void resetstate(void){
	dc = durch;
	printf("\x1B[0m");
}

void stateley(char c){
	if(c == '}'){
		dump();
		putc(c, stdout);
		resetstate();
	} else {
		//made it through wpi{
		if(c == *dc){
			pushc(c);
			dc++;
		} else {
			dump();
			putc(c, stdout);
			dc = durch;
		}
		if(!*dc){
			printf("\x1B[31m");
			dump();
			dc = durch;
		}
	}
}


#define NUMCHARS 3

int main(const int argc, const char ** argv){
	resetstate();
	FILE *f;
	char biffbuff[NUMCHARS+1] = {0};
	if(argc < 2){
		printf("Usage: %s some_file\n", argv[0]);
		return 1;
	}
	f = fopen(argv[1], "r");
	if(!f){
		printf("Unable to open %s\n", argv[1]);
		printf("Usage: %s some_file\n", argv[0]);
		return 2;
	}


	int biffcounter = 0;
	int c = 0;
	while((c = fgetc(f)) != EOF){
		if(isprint(c)){
			if(biffcounter < NUMCHARS){
				biffbuff[biffcounter] = c;
			} else {
				if (biffcounter == NUMCHARS) {
					int i = 0;
					for (i = 0; i < biffcounter; i++){
						stateley(biffbuff[i]);
					}
				}
				stateley(c);
			}
			biffcounter++;
		} else {
			resetstate();
			if(biffcounter > NUMCHARS)
				putc('\n', stdout);
			biffcounter = 0;
		}
	}
	if(biffcounter >=4)
		putc('\n', stdout);
	if(f)fclose(f);
	if(buf)free(buf);
	return 0;
}
