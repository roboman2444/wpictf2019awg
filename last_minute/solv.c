#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>

#include <time.h>

time_t time(time_t *tloc){
	return 1555286399;
}