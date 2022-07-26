#include<netinet/in.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

#define port1 8080

void main()
{
	int server1_fd,server2_fd,server3_fd,server4_fd,client_fd;
	int opt=1;
	
	int n[1];
	
	
	
	struct sockaddr_in server1_addr,server2_addr,server3_addr,client_addr;
	
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
	server1_addr.sin_addr.s_addr=INADDR_ANY;	
	
	
	
	if(bind(server1_fd,(struct sockaddr*)&server1_addr,sizeof(server1_addr))<0)
	{
		perror("Binding failed");
		exit(0);
	}
	
	
	
	listen(server1_fd,5);
	
	int c=sizeof(struct sockaddr_in);
	
	client_fd=accept(server1_fd,(struct sockaddr*)&client_addr,(socklen_t *)&c);
	
	if(client_fd<0)
	{
		perror("Accept failed");
		exit(0);
	}
	
	read(client_fd,n,sizeof(int));
	
	printf("Message from client1 through tcp is : %d\n",n[0]);
	
	
	int out[1];
	out[0]=n[0]*n[0];
	
	
	client_fd=accept(server1_fd,(struct sockaddr*)&client_addr,(socklen_t *)&c);
	send(client_fd,out,sizeof(out),0);
	
	
	
	
	
	
	
	
}
	
	
	
	
	
	
	
	
	
	
	
	
