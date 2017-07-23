#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<memory.h>

int main(int argc, char *argv[])
{
	int server_sockfd;
	int client_sockfd;
	int len;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int sin_size;
	char buf[BUFSIZ];
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(8000);

	if((server_sockfd = socket(PF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket");
		return 1;
	}
	if(bind(server_sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))<0)
	{
		perror("bind");
		return 1;
	}
	listen(server_sockfd,5);
	sin_size = sizeof(struct sockaddr_in);
	if((client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_addr,&sin_size))<0)
	{
		perror("accept");
		return 1;
	}
	printf("accept client %s\n",inet_ntoa(client_addr.sin_addr));
	len = send(client_sockfd,"welcom to my server\n",21,0);
	while((len = recv(client_sockfd,buf,BUFSIZ,0))>0)
	{
		buf[len] = '\0';
		printf("%s\n",buf);
		if(send(client_sockfd,buf,len,0)<0)
		{
			perror("write");
			return 1;
		}
	}
	close(client_sockfd);
	close(server_sockfd);
	return 0;
}

