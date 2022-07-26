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
	
	
	//127.0.0.1
	//172.20.34.222
	//172.20.33.64
	
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	/*
	if(inet_pton(AF_INET,"172.20.33.64",&server_addr.sin_addr)<0)
	{
		perror("Connection failed");
		exit(0);
	}
	*/
	
	if(connect(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		perror("connect failed");
		exit(0);
	}
	printf("\nEnter the window size: ");
	int n;
	scanf("%d",&n);
	send(server_fd,n,sizeof(int),0);
	
	int d[10]={1000,900,800,700,600,500,400,300,200,100};
	int c[0];
	char a[0][4];
	
	int i=0,j=0;
	while(i<n)
	{
		b[i]=d[i];
		
		i++;
	}
	send(server_fd,b,sizeof(int)*n,0);
	while(j<10)
	{
		sleep(1);
		c[0]=d[i];
		recv(server_fd,a[0],sizeof(int),0);
		if(strcmp("ACK",a[0])==0)
		{
			printf("\n%d Acknowledgement received.",d[i]);
			i++;
		}
		else
		{
			printf("\nResending frame: %d",d[i]);
		}
	}
	
	
}
	
	
	
	
	
	
	
	
	
	
	
	
