#include<netinet/in.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define port 8080

void main()
{
	int server_fd,client_fd;
	int opt=1;
	
	int a[100];
	
	printf("\nEnter the size of the array : ");
	int n;
	scanf("%d",&n);
	
	printf("\nEnter %d numbers into the array : ",n);
	
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	
	
	
	
	
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
	if(inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr)<0)
	{
		perror("Connection failed");
		exit(0);
	}
	
	if(connect(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		perror("Binding failed");
		exit(0);
	}
	
	
	int out[3];
	
	write(server_fd,a,n*sizeof(int));
	read(server_fd,out,3*sizeof(int));
	
	printf("Max : %d\n",out[0]);
	
	printf("Min : %d\n",out[1]);
	
	printf("Avg : %d\n",out[2]);
	
	
}
	
	
	
	
	
	
	
	
	
	
	
	
