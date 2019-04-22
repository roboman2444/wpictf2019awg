#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

const char * durch = "wpi{";
const char * eurch = "}";
const char * lurch = "What_do_you_mean_I_SEE_AHH_SKI";

#define NUMCHARS 3

int main(const int argc, const char ** argv){
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
			if(biffcounter >= NUMCHARS)
				putc('\n', stdout);
			biffcounter = 0;
		}
	}
	if(biffcounter >=4)
		putc('\n', stdout);
	if(f)fclose(f);
	return 0;
}
