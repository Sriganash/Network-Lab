#include<netinet/in.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


/*https://drive.google.com/file/d/1rtZQEW1bOGBpvhX0H8nvFt7OqK6GoQW1/view?usp=sharing*/


#define port 8080

void main()
{
	int server_fd,client_fd;
	int opt=1;
	FILE *fp;
	fp=fopen("file1.txt","w");
	
	
	
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
	
	recv(client_fd,msg,1000*sizeof(char),0);
	char buffer[1000];
	snprintf(buffer, 1000*sizeof(char), "wget -P /home/user/Desktop/network/8/new %s", msg);
	system(buffer);
	write(client_fd,"/home/user/Desktop/network/8/new",sizeof("/home/user/Desktop/network/8/new"));
	
}
	
	
	
	
	
	
	
	
	
	
	
	
