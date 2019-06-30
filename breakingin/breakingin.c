#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <errno.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#define TRUE 1
#define FALSE 0


#define MEMSIZE 65536
int32_t mem[MEMSIZE] ={0};

void error(int retval, char * err){
	puts(err);
	exit(retval);
}
#define MAGICMAN 0x133769


//may need to give them a hint that b is a pointer to a list of args

int do_write(const uint32_t arg){
	if(arg > MEMSIZE - 3) error(4, "Syscall arg outside of bounds!\n");
	int fd = mem[arg];
	void * buf = mem + (uint32_t)mem[arg+1];
	size_t count = mem[arg+2];
	if(buf < (void*)mem || buf + count > (void*)mem + sizeof(mem)) return -1;
	return write(fd, buf, count);
}
int do_close(const uint32_t arg){
	if(arg > MEMSIZE - 1) error(4, "Syscall arg outside of bounds!\n");
	int fd = mem[arg];
	return close(fd);
}
int do_pipe(const uint32_t arg){
	if(arg > MEMSIZE - 1) error(4, "Syscall arg outside of bounds!\n");
	void * pipefd  = mem+(uint32_t)mem[arg];
	if(pipefd < (void*)mem || pipefd + 2 * sizeof(uint32_t) > (void*)mem + sizeof(mem)) return -1;
	return pipe(pipefd);
}
int do_pipe2(const uint32_t arg){
	if(arg > MEMSIZE - 2) error(4, "Syscall arg outside of bounds!\n");
	void * pipefd  = mem+(uint32_t)mem[arg];
	int flags = mem[arg+1];
	if(pipefd < (void*)mem || pipefd + 2 * sizeof(uint32_t) > (void*)mem + sizeof(mem)) return -1;
	return pipe2(pipefd, flags);
}
int do_dup(const uint32_t arg){
	if(arg > MEMSIZE - 1) error(4, "Syscall arg outside of bounds!\n");
	int oldfd = mem[arg];
	return dup(oldfd);
}
int do_dup2(const uint32_t arg){
	if(arg > MEMSIZE - 2) error(4, "Syscall arg outside of bounds!\n");
	int oldfd = mem[arg];
	int newfd = mem[arg+1];
	return dup2(oldfd, newfd);
}
int do_socket(const uint32_t arg){
	if(arg > MEMSIZE - 3) error(4, "Syscall arg outside of bounds!\n");
	int domain = mem[arg];
	int type = mem[arg+1];
	int protocal = mem[arg+2];
	return socket(domain, type, protocal);
}
int do_connect(const uint32_t arg){
	if(arg > MEMSIZE - 3) error(4, "Syscall arg outside of bounds!\n");\
	int sockfd = mem[arg];
	void *addr = mem + mem[arg+1];
	socklen_t addrlen = mem[arg+2];
	if(addr < (void*)mem || addr + addrlen > (void*)mem + sizeof(mem)) return -1;
//	((struct sockaddr_in *)addr)->sin_family = AF_INET;
//	((struct sockaddr_in *)addr)->sin_addr.s_addr = inet_addr("127.0.0.1");
//	((struct sockaddr_in *)addr)->sin_port = htons(21845);


//	printf("%i, %i %i %08x\n", sizeof(struct sockaddr_in),
//((struct sockaddr_in *)addr)->sin_family,
//((struct sockaddr_in *)addr)->sin_port,
//((struct sockaddr_in *)addr)->sin_addr);

//	printf("Made it here! %i %p %i\n", sockfd, addr, addrlen);
//	int res = connect(sockfd, addr, addrlen);
//	printf("errno %i\n", errno);
//	return res;
	return connect(sockfd, addr, addrlen);
}

char * quips[] = {	"You think im just gonna run %s?\n",
			"This is not the %s you are looking for.\n",
			"Go %s yourself!\n",
			"%s? Now why would i do that?\n",
			"%s? Nah, never heard of him.\n",
			"Oh man this challenge would be so much easier if you could just system(\"%s\");\n",
			"flag is WPI{%s}\n\n\nOh wait no it isn't.\n"
		};
int do_execve(const uint32_t arg){
	if(arg > MEMSIZE - 3) error(4, "Syscall arg outside of bounds!\n");
//	return -1;
	//todo argv, envp
	void * fname = mem + mem[arg];
	if(fname == mem) fname = "NULL";
	else if(fname < (void*)mem || fname + strlen(fname)+1 > (void*)mem + sizeof(mem) || !strlen(fname)) fname = "arg 0 OOB";
	printf(quips[rand() % (sizeof(quips)/sizeof(*quips))], fname);
	return -1;
}
int do_sendto(const uint32_t arg){
	if(arg > MEMSIZE - 6) error(4, "Syscall arg outside of bounds!\n");
	int sockfd = mem[arg];
	void * buf = mem + mem[arg+1];
	size_t len = mem[arg+2];
	int flags = mem[arg+3];
	void * sockaddr = mem + mem[arg+4];
	socklen_t addrlen = mem[arg+5];
	if(buf < (void*)mem || buf + len > (void*)mem + sizeof(mem)) return -1;
	if(sockaddr < (void*)mem || sockaddr + addrlen > (void*)mem + sizeof(mem)) return -1;
	if(sockaddr == mem && addrlen == 0) sockaddr = 0;

//	printf("sendto %i %p %i\n", sockfd, buf, len);
	return sendto(sockfd, buf, len, flags, sockaddr, addrlen);
}
int do_recvfrom(const uint32_t arg){
	if(arg > MEMSIZE - 6) error(4, "Syscall arg outside of bounds!\n");
	int sockfd = mem[arg];
	void * buf = mem + mem[arg+1];
	size_t len = mem[arg+2];
	int flags = mem[arg+3];
	void * sockaddr = mem + mem[arg+4];
	void * addrlen = mem + mem[arg+5];
	if(buf < (void*)mem || buf + len > (void*)mem + sizeof(mem)) return -1;

	if(addrlen < (void*)mem || addrlen + sizeof(socklen_t) > (void*)mem + sizeof(mem)) return -1;
	if(addrlen == mem){
		addrlen = NULL;
		sockaddr = NULL;
	} else {
		if(sockaddr < (void*)mem || sockaddr + *(socklen_t *)addrlen > (void*)mem + sizeof(mem)) return -1;
		if(sockaddr == mem) sockaddr = 0;
	}
	//todo fix addrlen?
//	printf("recvfrom %i %p %i\n", sockfd, buf, len);
	return recvfrom(sockfd, buf, len, flags, sockaddr, addrlen);
}
//todo pause
//todo sendfile
//todo splice?
//todo some way to idk
//todo set up an alarm


void process_syscall(const uint32_t a, const uint32_t b, const uint32_t c){
	//a is syscall number, b is syscall args, c is syscall ret
//	printf("SYscall %i\n", mem[a]);
	switch(mem[a]){
		case 1:		//write
			mem[c] = do_write(b);
			break;
		case 3:		//close
			mem[c] = do_close(b);
			break;
		case 22:	//pipe
			mem[c] = do_pipe(b);
			break;
		case 32:	//dup
			mem[c] = do_dup(b);
			break;
		case 33:	//dup2
			mem[c] = do_dup2(b);
			break;
		case 41:	//socket
			mem[c] = do_socket(b);
			break;
		case 42:	//connect
			mem[c] = do_connect(b);
			break;
		case 44:
			mem[c] = do_sendto(b);
			break;
		case 45:
			mem[c] = do_recvfrom(b);
			break;
		case 59:	//execve
			mem[c] = do_execve(b);
			break;
		case 60:	//exit
			exit(mem[b]);
			break;
		case 293:
			do_pipe2(b);
			break;
		default:
			printf("Unimplemented syscall %i\n", mem[a]);
			break;
	}
//	printf("%i returned %i\n", mem[a], mem[c]);
}

static inline void doop(const uint32_t op, const uint32_t a, const uint32_t b, const uint32_t c){
	switch(op){
		case 1: mem[c] = mem[a] + mem[b]; break;
		case 2: mem[c] = mem[a] - mem[b]; break;
		case 3: mem[c] = mem[a] * mem[b]; break;
		case 4: mem[c] = mem[a] / mem[b]; break;
		case 5: mem[c] = mem[a] % mem[b]; break;
		case 6: mem[c] = mem[a] & mem[b]; break;
		case 7: mem[c] = mem[a] | mem[b]; break;
		case 8: mem[c] = mem[a] ^ mem[b]; break;
		case 9: mem[c] = ~mem[a]; break;
		case 10: mem[c] = !mem[a]; break;
		case 11: mem[c] = mem[a] << mem[b]; break;
		case 12: mem[c] = (((unsigned int*)mem)[a] >> mem[b]); break;
		case 13: mem[c] = mem[a] >> mem[b]; break;
		case 14: mem[c] = mem[a] > mem[b]; break;
		case 15: mem[c] = mem[a] == mem[b]; break;
		default: break;
	}
	if(op == MAGICMAN){
		process_syscall(a, b, c);
	}
}

uint64_t executionloop(void){
	uint32_t ip;
	uint64_t i;
	for(i = 0; i < 1000000 && (ip = mem[0]); i++, mem[0]+=4){
		if(ip > MEMSIZE-4) error(3, "Instruction pointer out of bounds!\n");
		uint32_t op =mem[ip];
		uint32_t a = mem[ip+1];
		uint32_t b = mem[ip+2];
		uint32_t c = mem[ip+3];
		if(a > MEMSIZE-1 || b > MEMSIZE-1 || c > MEMSIZE-1) error(3, "Memory access outside of bounds!\n THAT DONT WORK THIS TIME\n");

//		printf("did op %u %u %u %u at ip %u\n", op, a, b, c, ip);
		doop(op, a, b, c);
//		i = 0;
	}
	return i;
}



int main(void){

	srand(time(0));
	size_t readinsize = 0;
	printf("Welcome to my little vm, running roboarchNG (with a special secret op added :P) with a memory size of %lu\n", sizeof(mem));
	printf("Enter a size for the binary (max %lu):\n", sizeof(mem));
	scanf("%lu", &readinsize);
	if(readinsize > sizeof(mem)){
		printf("Read size %lu too large!\n", readinsize);
		exit(1);
	} else if (!readinsize){
		printf("Zero bytes, really?\n");
		exit(1);
	}
	printf("Ok, give me %lu bytes:\n", readinsize);

	size_t tread;
	for(tread = 0; tread < readinsize; tread += read(STDIN_FILENO, ((char*)mem)+tread, sizeof(mem)-tread)) printf("teread %lu\n", tread);
	uint64_t res = executionloop();
	size_t zeroomit;
	for(zeroomit = sizeof(mem); zeroomit && !((char*)mem)[zeroomit-1]; zeroomit--);
	printf("Executed %llu cycles! Sending back %lu bytes (omitting trailing nulls)\n", res, zeroomit);

	write(STDOUT_FILENO, mem, zeroomit);

	printf("All done!\n");
	exit(0);
}
