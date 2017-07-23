#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

void pipe_test()
{
	int fd[2];
	int count =0;
	char buf[65536] = {0};
	int n;

	if(pipe(fd)<0)
	{
		perror("fail to create pipe");
		exit(0);
	}
	while(1)
	{
		write(fd[1],"a",sizeof(char));
		printf("count = %d\n",++count);
		if(count==65535)
			break;
	}
	if((n = read(fd[0],buf,sizeof(buf)))<0)
	{
		perror("fail to read pipe");
		exit(0);
	}
//	printf("read %d bytes : %s\n",n,buf);
}

void close_write()
{
	int n;
	int fd[2];
	int count = 0;
	char buf[100] = {0};
	if(pipe(fd)<0)
	{
		perror("fail to create pipe");
		exit(0);
	}
	close(fd[1]);
	if((n = read(fd[0],buf,sizeof(buf)))<0)
	{
		perror("fail to read pipe");
		exit(0);
	}
	printf("read %d bytes: %s\n",n,buf);	
}

int child_read_pipe(int fd)
{
	char buf[10];
	int n = 0;
	while(1)
	{
		n = read(fd,buf,sizeof(buf));
		buf[n] = '\0';
		printf("read %d bytes : %s\n",n,buf);
		if(strncmp(buf,"quit",4) == 0)
			break;
	}
	return 0;
}
int father_write_pipe(int fd)
{
	char buf[100] = {0};
	while(1)
	{
		printf(">");
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1] = '\0';
		write(fd,buf,strlen(buf));
		usleep(500);
		if(strncmp(buf,"quit",4) == 0)
			break;
	}	
	return 0;
}
void father_to_child()
{
	int pid;
	int fd[2];
	
	if(pipe(fd)<0)
	{
		perror("fail to create pipe");
		exit(0);
	}
	if((pid = fork()) < 0)
	{
		perror("fail to fork");
		exit(0);
	} else if(pid == 0) {
		close(fd[1]);
		child_read_pipe(fd[0]);
	} else {
		close(fd[0]);
		father_write_pipe(fd[1]);
	}
}

int close_read()
{
	int n;
	int pid;
	int fd[2];
	char buf[100] = {0};
	if(pipe(fd)<0)
	{
		perror("fail to create pipe");
		exit(0);
	}
	if((pid = fork()) < 0)
	{
		perror("fail to fork");
		exit(0);
	} else if(pid == 0) {
		close(fd[1]);
		sleep(5);
		close(fd[0]);
		printf("read port close\n");
		sleep(3);
	} else {
		close(fd[0]);
		while(1)
		{
			n = write(fd[1],buf,sizeof(buf));
			printf("write %d bytes to pipe\n",n);
		}
	}
	exit(EXIT_SUCCESS);
}
int main()
{
//	pipe_test();
	close_write();
	father_to_child();
	close_read();
	return 0;
}
