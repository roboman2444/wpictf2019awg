#include <stdio.h>
#include <stdlib.h>

#include <openssl/md5.h>

int main(void){
	MD5_CTX context;
	uint64_t digest[2];
	size_t i = 0;
	for(i = 0; i < 1000000; i++){
		srand(i);
		rand();
		rand();
		rand();
		int uuid = rand();
		MD5_Init(&context);
		MD5_Update(&context, &uuid, sizeof(uuid));
		MD5_Final((unsigned char *)digest, &context);
	}
}
