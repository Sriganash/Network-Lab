#include<netinet/in.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define port 8080

void main()
{
	int server_fd,client_fd;
	int opt=1;
	
	char msg[50];
	
	
	struct sockaddr_in server_addr,client_addr;
	
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	
	if(server_fd<0)
	{
		perror("Socket creation failed");
		exit(0);
	}
	
	if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt))<0)
	{
		perror("Socket manipulation failed");
		exit(0);
	}
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=INADDR_ANY;	
	
	if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		perror("Binding failed");
		exit(0);
	}
	
	
	listen(server_fd,5);
	
	int c=sizeof(struct sockaddr_in);
	
	client_fd=accept(server_fd,(struct sockaddr*)&client_addr,(socklen_t *)&c);
	
	if(client_fd<0)
	{
		perror("Accept failed");
		exit(0);
	}
	int n;
	recv(client_fd,n,sizeof(int),0);
	int b[n];
	int a[0];
	char ack[50];
	int i=0;
	while(i<10)
	{
		recv(client_fd,a,sizeof(int),0);
		
			printf("RECEIVED FRAME: %d\n",d[i]);
			printf("do you want to ACK or NACK ? ");
			scanf(" %s",ack);
			if(strcmp(ack,"ACK")==0)
			{
				send(client_fd,"ACK",sizeof("ACK"),0);
				i++;
			}
			else
			{
				send(client_fd,"NACK",sizeof("NACK"),0);
			}
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
