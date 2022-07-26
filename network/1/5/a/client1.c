#include<netinet/in.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define port1 8080

void main()
{
	int server1_fd,server2_fd;
	int opt=1;
	
	char msg[50];
	
	printf("\nEnter the string : ");
	
	scanf(" %s",msg);
	
	struct sockaddr_in server1_addr,client_addr;
	
	server1_fd=socket(AF_INET,SOCK_STREAM,0);
	
	
	if(server1_fd<0)
	{
		perror("Socket creation failed");
		exit(0);
	}
	
	if(setsockopt(server1_fd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt))<0)
	{
		perror("Socket manipulation failed");
		exit(0);
	}
	
	server1_addr.sin_family=AF_INET;
	server1_addr.sin_port=htons(port1);
	server1_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	
	if(connect(server1_fd,(struct sockaddr*)&server1_addr,sizeof(server1_addr))<0)
	{
		perror("Binding failed");
		exit(0);
	}
	
	
	
	
	write(server1_fd,msg,sizeof(msg));
	printf("\nMessage send to server using tcp is : %s\n",msg);
	
	
	
	
	
	
}
	
	
	
	
	
	
	
	
	
	
	
	
