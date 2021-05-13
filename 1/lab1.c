#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
	pid_t pid;
	pid = fork();
	if(pid<0){
		printf("failed\n");
	}else if(pid==0){
		pid_t yapid;
		yapid = fork();
		if(yapid<0){
			printf("yaprocess failed");
		}else if (yapid == 0){
			FILE *fp = fopen("./123.txt", "r");
			char ss[1000]; fscanf(fp, "%s", ss);	
			printf("file: %s\n", ss);			
			printf("ch pid: %d\n", getpid());
			fclose(fp);			
		}else {
			wait();
			printf("My son has finished his homework!");	
		}
	}
	return 0;
}
