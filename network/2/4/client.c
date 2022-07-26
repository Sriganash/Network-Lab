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
	
	
	struct sockaddr_in server_addr,client_addr;
	
	memset(&server_addr,0,sizeof(server_addr));
	
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
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(connect(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		perror("connect failed");
		exit(0);
	}

	char msg[1024];


	
	send(server_fd,"SMTP REQUEST FROM CLIENT",sizeof("SMTP REQUEST FROM CLIENT"),0);
	recv(server_fd,msg,1024,0);
	printf("\nS :> %s\n",msg);

	L1:printf("\nEnter the sender E-Mail address: ");
	char sender[100];
	scanf(" %s",sender);
	send(server_fd,sender,sizeof(sender),0);
	recv(server_fd,msg,1024,0);
	if(strcmp(msg,"Invalid email id....")==0)
	{
		printf("\n%s\n",msg);
		goto L1;
	}
	else
		printf("\nS :> 250 : Hello <%s>....%s....\n",sender,msg);

	L2:printf("\nEnter the receivor E-Mail address: ");
	char receivor[100];
	scanf(" %s",receivor);
	send(server_fd,receivor,sizeof(receivor),0);
	recv(server_fd,msg,1024,0);
	if(strcmp(msg,"Invalid email id....")==0)
	{
		printf("\n%s\n",msg);
		goto L2;
	}
	else
		printf("\nS :> 250 : Hello <%s>....%s....\n",receivor,msg);

	send(server_fd,"DATA",sizeof("DATA"),0);
	recv(server_fd,msg,1024,0);
	printf("\nS :> %s\n",msg);

	printf("\n-----------------------------------------------\n");
	strcpy(msg,"");
	char buffer[1024];
	strcpy(buffer,"");
	do
	{

		strcpy(msg,"");
		scanf(" %s", msg);
		strcat(buffer,msg);
		
		if(msg[strlen(msg)-1]==',' || msg[strlen(msg)-1]=='.' ||msg[strlen(msg)-1]=='!')
			strcat(buffer,"\n");
		else
			strcat(buffer," ");

	}while(strcmp(msg,":)")!=0);
	printf("\n-----------------------------------------------\n");

	send(server_fd,buffer,sizeof(char)*strlen(buffer),0);
	send(server_fd,"QUIT",sizeof("QUIT"),0);
	recv(server_fd,msg,1024,0);
	printf("\nS :> %s\n",msg);


}


	














