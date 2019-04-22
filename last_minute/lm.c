#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>
#include <linux/fb.h>
#include <stdint.h>


#include "paxels.h"
struct fb_fix_screeninfo finfo;
struct fb_var_screeninfo vinfo;



int main(void){
	int i;
	int fabood;
//	srand(1555286399/60);	//todo get right time offset
	srand(time(0)/60);	//todo get right time offset
//	srand(time(0));	//todo get right time offset
//	srand(1337/60);
	fabood = open("/dev/fb0", O_RDWR);
	ioctl(fabood, FBIOGET_VSCREENINFO, &vinfo);
	vinfo.grayscale = 0;
	vinfo.bits_per_pixel=32;
	for(i = 0; i < 31337; i++){
		//some dumb shit to confugse
		ioctl(fabood, FBIOPUT_VSCREENINFO, &vinfo);
		i = i * 13 + *((uint8_t * ) &vinfo);
		vinfo.accel_flags = i;
	}
	ioctl(fabood, FBIOGET_VSCREENINFO, &vinfo);
	ioctl(fabood, FBIOGET_FSCREENINFO, &finfo);
	printf("%i\n", finfo.line_length);
	if(finfo.line_length < 6400){	//1600
		printf("Ectomorph\n");
		return 1;
	}
	if(finfo.line_length > 6400){
		printf("Endomorph\n");
		return 1;
	}
	printf("Mesomorph\n");


	int dt[8] = { 1, -1, finfo.line_length/4, -(finfo.line_length/4),
		1 + (finfo.line_length/4), 1-(finfo.line_length/4),
		-1 + (finfo.line_length/4), -1-(finfo.line_length/4)};

	size_t fuk = (finfo.line_length*vinfo.yres)/4;
//	printf("fuk %i\n", fuk);
	char * fbp = mmap(0, fuk*4, PROT_READ | PROT_WRITE, MAP_SHARED, fabood, (off_t) 0);
	size_t indx = 1337;
	for(i = 0; i < PIXIES;i++){
		indx += rand();
		// set dir to 1 if you want no dir
		int dir = dt[rand() & 7];
		uint32_t fukt = baboof[i*2];
		uint32_t ccunt = baboof[i*2+1];
		while(ccunt--){
			((uint32_t*)fbp)[indx%fuk] = fukt;
			indx+=dir;
		}
	}
}
