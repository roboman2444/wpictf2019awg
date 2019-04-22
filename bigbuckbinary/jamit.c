#include <stdio.h>
#include <stdlib.h>



char * needle = "OggS";
int needlestate = 0;


int writeitout(char *f, FILE * output){
	FILE * fo = fopen(f, "rb");
	int c;
	while((c = fgetc(fo)) != EOF){
		fputc(c, output);
	}
}

int main(int argc, char ** argv){
	FILE * output = fopen(argv[1], "wb");
	FILE * vidya = fopen(argv[2], "rb");

	int fcnt = 3;
	int c;
	while((c = fgetc(vidya)) != EOF){
		if(fcnt < argc){
			if(c == needle[needlestate]){
				needlestate++;
			} else {
				if(needlestate){
					fwrite(needle, needlestate, 1, output);
				}
				needlestate = 0;
				fputc(c, output);
			}

			//we reached needlestate
			if(!needle[needlestate]){
				if(!(rand()%10000)){
					writeitout(argv[fcnt], output);
					fcnt++;
				}
			}
		} else {
			fputc(c, output);
		}


	}

	printf("fcnt is %i\n", fcnt);

	return 0;
}
