#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>

#include <openssl/md5.h>

void init(void){
	struct timeval time;
	gettimeofday(&time, NULL);
	srand((time.tv_sec * 1000000) + (time.tv_usec));
}

void shell(void){
	execve("/bin/bash", 0, 0);
	exit(0);
}




int times = 0;
void logit(void){
	FILE *f;
	MD5_CTX context;
	uint64_t digest[2];
	char md5string[33];
	int uuid = rand();

	MD5_Init(&context);
	MD5_Update(&context, &uuid, sizeof(uuid));
	MD5_Final((unsigned char *)digest, &context);
	sprintf(md5string, "%" PRIx64 "%" PRIx64 , digest[0], digest[1]);

	printf("You.dumbass is not in the sudoers file.  This incident will be reported.\n");
	printf("Incident UUID: %s\n", md5string);

	f = fopen("/dev/null", "w");
	if(!f) return;
	fprintf(f, "Incident %s: That dumbass forgot his password %s\n", md5string, times ? "(Again)" : "");
	fclose(f);
	times++;
}

void stakcheck(uint64_t canary, uint64_t canary2){
	if(canary != canary2){
		printf("LARRY THE CANARY IS DEAD\n");
		exit(1);
	}
}

int checkpw(void){
	struct {
		uint64_t canary;
		char pwboofer[100];
		char * newy;
		uint64_t bettercanary;
	}locals;

	locals.canary = rand();
	locals.canary = (locals.canary << 32) ^ rand();
	locals.bettercanary = locals.canary;

	printf("Enter the password\n");
	fgets(locals.pwboofer, 0x100, stdin);

	locals.newy = strchr(locals.pwboofer, '\n');
	if(locals.newy) *locals.newy = 0;

	if(strcmp(locals.pwboofer, getenv("SECUREPASSWORD"))){
		stakcheck(locals.canary, locals.bettercanary);
		return 0;
	}

	stakcheck(locals.canary, locals.bettercanary);
	return 1;
}


void main(void){
	int i;
	init();
	printf("Welcome to the Super dooper securer shell! Now with dynamic stack canaries and incident reporting!\n");

	for(i = 0; i < 3; i++){
		if(i) printf("\nattempt #%i\n", i+1);
		if(checkpw()) shell();
		else logit();
	}
	printf("\nToo many wrong attempts, try again later\n");
}
