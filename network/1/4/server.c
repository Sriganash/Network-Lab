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
	
	int a[10];
	int out[3];
	int n=recv(client_fd,a,100*sizeof(int),0)/sizeof(int);
	
	int min=a[0];
	int max=a[0];
	int sum=a[0];
	for(int i=1;i<n;i++)
	{
		if(a[i]>max)
			max=a[i];
		else if(a[i]<min)
			min=a[i];
		sum+=a[i];
	}
	
	out[0]=max;
	out[1]=min;
	out[2]=sum/n;
	
	printf("Max : %d\n",out[0]);
	
	printf("Min : %d\n",out[1]);
	
	printf("Avg : %d\n",out[2]);
	
	
	write(client_fd,out,sizeof(out));
	
}
	
	
	
	
	
	
	
	
	
	
	
	
