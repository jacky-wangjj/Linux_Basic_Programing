#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<memory.h>

#define MAX 655360

int main(int argc,char *argv[])
{
	int n,fd;
	char buf[MAX];
	if(argc < 2) {
		fprintf(stderr,"usage : %s argv[1]\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	if(mkfifo(argv[1],0666) < 0 && errno != EEXIST) {
		fprintf(stderr,"fail to mkfifo %s : %s\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);
	}
	if((fd = open(argv[1],O_RDONLY)) < 0) {
		fprintf(stderr,"fail to open %s : %s\n",argv[1],strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("open for read success\n");
	while(1)
	{
		printf(">");
		scanf("%d",&n);
		n = read(fd,buf,n);
		printf("read %d bytes : %s\n",n,buf);
		if(strcmp(buf,"quit") == 0)
			break;
		memset(buf,0,MAX);
	}
	exit(EXIT_SUCCESS);
}
