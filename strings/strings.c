#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

char * durch = "WPI{";
char * lurch = "warbleglarblesomejunkWPI{What_do_you_mean_I_SEE_AHH_SKI}0x13376969";


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

int sawwpi = 0;
char *dc;
void resetstate(void){
	sawwpi = 0;
	dc = durch;
	dump();
}

void stateley(char c){
	pushc(c);
	if(sawwpi){
		if(c == '}'){
			printf("\x1B[31m");
			resetstate();
			printf("\x1B[0m");
		}
	} else {
		if(c == *dc){
			dc++;
		} else {
			resetstate();
		}
		//made it through wpi{
		if(!*dc){
			sawwpi = 1;
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
char *stayinschool = "This code/algorithm is probably janky as fuck. I wrote it when i was drunk. (like all good challenges)";
char * yeet = "When you see that oh-ex four one four one four one four one you know its about to get fun\n";
char * ss = "rip be like https://www.youtube.com/watch?v=rDlI6itmr34";
