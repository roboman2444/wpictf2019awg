#include <stdio.h>
#include <stdlib.h>

#include <openssl/md5.h>

#include <inttypes.h>
#include <sys/time.h>

uint64_t ref[2] = {0};

void getcanary(unsigned int seed){
	srand(seed);
	rand(); //first canary
	rand();
	rand();	//incident id

	uint64_t canary = 0;
	canary = rand();
	canary = (canary << 32) ^ rand();
	printf("Canary is %" PRIx64 "\n", canary);
}

int scan(unsigned int start){
	MD5_CTX context;
	uint64_t digest[2] ={0};
	size_t i = 0;
	printf("testing %i\n", start);
	for(i = 0; i < 1000000; i++, start++){
		srand(start);
//		rand();
		rand();
		rand();
		int uuid = rand();
		MD5_Init(&context);
		MD5_Update(&context, &uuid, sizeof(uuid));
		MD5_Final((unsigned char *)digest, &context);

		if(digest[0] == ref[0] && digest[1] == ref[1]){
			printf("%i matches.... "  "%" PRIx64 "%" PRIx64 "\n", start, digest[0], digest[1]);
			getcanary(start);
			return 1;
		}
	}
	return 0;
}
int main(int argc, char ** argv){
	struct timeval time;
	gettimeofday(&time, NULL);

	sscanf(argv[1],  "%08x%08x%08x%08x" , ((uint8_t*)&ref[0])+4, &ref[0], ((uint8_t*)&ref[1])+4, &ref[1]);
//	sscanf(argv[1],  "%I64x%I64x" , &ref[0], &ref[1]); // uint64_t is fucky with sscanf?

	printf("looking for " "%" PRIx64 "%" PRIx64 "\n", ref[0], ref[1]);


	int ofs = 0;


	unsigned int ttime = (time.tv_sec+ofs) * 1000000;
	while(!scan(ttime) ){
		ofs = (-ofs) - (ofs >= 0);
		ttime = (time.tv_sec + ofs) * 1000000;
	}

}
