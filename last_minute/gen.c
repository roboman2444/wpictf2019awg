#include <stdio.h>
#include <stdlib.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define PIXIES (1<<18)

//int ralee[PIXIES];

int x, y, n;
uint8_t *data;

uint32_t genfukt(int ofs){
	uint32_t fukt = 0xFFFFFFFF;

	uint8_t *bukt = (uint8_t*)&fukt;

	uint8_t *bof = data + ofs*n;


	switch(n){
		case 1:
		case 2:
			bukt[0] = bukt[1] = bukt[2] = bof[0];
		break;
		case 4:
			bukt[3] = bof[3];
		case 3:
			bukt[2] = bof[0]&0xf0;
			bukt[1] = bof[1]&0xf0;
			bukt[0] = bof[2]&0xf0;
		break;
		default:
			printf("We ficed!\n");
			exit(111);
	}
	return fukt;
}



int dt[8];
void gendt(void){
	dt[0] = 1;
	dt[1] = -1;
	dt[2] = x;
	dt[3] = -x;
	dt[4] = 1+x;
	dt[5] = 1-x;
	dt[6] = -1+x;
	dt[7] = -1-x;
}

int main(int argc, char ** argv){
	if(argc < 3){
		printf("usage %s image_file time_int\n", argv[0]);
		return 1;
	}
	int tseed = atoi(argv[2]);
	char *fuggit = argv[1];
	srand(tseed/60);
//	srand(time(0)+30);
//	srand(1337);

	data = stbi_load(fuggit, &x, &y, &n, 0);
	gendt();
	size_t fuk = x * y;

	printf("//%i %i %i\n", x, y, n);
	printf("#define PIXIES %i\n", PIXIES);
//	printf("int baboof[PIXIES*2] = {");
	printf("uint32_t baboof[PIXIES*2] = {");
	size_t indx = 1337;
	int i;
	uint32_t prevthing = 0;
	for(i = 0; i < PIXIES; i++){
		//get random start pos
		indx += rand();
		//direction is

//		int dir = 1 - 2 * (indx & 0x1);
//		dir *= ( x*((indx>>1) & 0x1));
		int dir = dt[rand() & 7];
		size_t ccunt = 0;
		uint32_t prevthing;
		prevthing =  genfukt(indx%fuk);
		for(ccunt = 0; ccunt< x && ccunt < y && prevthing ==genfukt(indx%fuk); indx+=dir, ccunt++);
		printf(" %i, %i,", prevthing, ccunt);
	}
	stbi_image_free(data);
	printf("};\n");
	return 0;
}



//porogrammed when i was REALLY DRUNK
