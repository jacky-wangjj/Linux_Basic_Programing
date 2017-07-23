#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<memory.h>

int main(int argc, char *argv[])
{
	int client_sockfd;
	int len;
	struct sockaddr_in server_addr;
	char buf[BUFSIZ];
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(8000);

	if((client_sockfd = socket(PF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket");
		return 1;
	}
	if(connect(client_sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))<0)
	{
		perror("connect");
		return 1;
	}
	printf("connect to server\n");
	len = recv(client_sockfd,buf,BUFSIZ,0);
	buf[len] = '\0';
	printf("%s\n",buf);
	while(1)
	{
		printf("enter string to send:");
		scanf("%s",buf);
		len = send(client_sockfd,buf,strlen(buf),0);
		if(!strcmp(buf,"quit"))
			break;
		memset(buf,0,BUFSIZ);
		len = recv(client_sockfd,buf,BUFSIZ,0);
		buf[len] = '\0';
		printf("recieve form server: %s\n",buf);
	}
	close(client_sockfd);
	return 0;
}

