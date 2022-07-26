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
	
	server_fd=socket(AF_INET,SOCK_DGRAM,0);
	
	/*memset(&server_addr,0,sizeof(server_addr));
	memset(&client_addr,0,sizeof(client_addr));*/
	
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
	
	int c=sizeof(client_addr);
	recvfrom(server_fd,msg,1024,MSG_WAITALL,(struct sockaddr*) &client_addr,&c);
	
	printf("Message from client is : %s\n",msg);
	
	sendto(server_fd,"Hello Client",sizeof("Hello Client"),MSG_CONFIRM,(struct sockaddr*) &client_addr,sizeof(client_addr));
	
}
	
	
	
	
	
	
	
	
	
	
	
	
