#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

static int k = 1;

void *create(void *arg){
	printf("a pthread created\n");
	printf("K=%d\n", k);
	printf("tid: %lld\n", (unsigned long long int)pthread_self());
	k = 1024;
	return (void * )0;
}

int main(){
	pthread_t l;
	k = 233;
	
	if(pthread_create(&l, NULL, create, NULL)){
		printf("failed\n");
		return 0;
	}else {
		sleep(1);
		printf("success\n");
		printf("K is shared, K = %d\n tid = %lld\n", k, (unsigned long long int)l);
		return 0;
	}
	printf("the pthread_t has %d Byte\n", sizeof(pthread_t));
	return 0;
}
