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

	
	
	struct sockaddr_in server_addr,client_addr;
	
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	
	memset(&server_addr,0,sizeof(server_addr));
	memset(&client_addr,0,sizeof(client_addr));
	
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

	int c=sizeof(struct sockaddr_in);
	
	listen(server_fd,5);
	client_fd=accept(server_fd,(struct sockaddr*)&client_addr,(socklen_t *)&c);
	
	if(client_fd<0)
	{
		perror("Accept failed");
		exit(0);
	}

	char buffer[1024];
	char msg[1024];

	char sender[100],receivor[100];

	recv(client_fd,msg,1024,0);
	printf("\nC :> %s\n",msg);

	send(client_fd,"220: server name",sizeof("220: server name"),0);

	L1:recv(client_fd,sender,1024,0);
	int amp=0,dot=0;
	for(int i=0;i<strlen(sender);i++)
	{
		if(sender[i]=='@' && amp==0 && dot==0)
		{
			amp=1;
		}
		else if(sender[i]=='.' && amp==1 && dot==0)
		{
			dot=1;
		}
	}
	if(amp==1 && dot ==1)
	{
		printf("\nC :> MAIL FROM: <%s>\n",sender);
	    send(client_fd,"Sender Ok....",sizeof("Sender Ok...."),0);
	}
	else
	{
		send(client_fd,"Invalid email id....",sizeof("Invalid email id...."),0);
		goto L1;
	}

	L2:recv(client_fd,receivor,1024,0);
	amp=0,dot=0;
	for(int i=0;i<strlen(receivor);i++)
	{
		if(receivor[i]=='@' && amp==0 && dot==0)
		{
			amp=1;
		}
		else if(receivor[i]=='.' && amp==1 && dot==0)
		{
			dot=1;
		}
	}
	if(amp==1 && dot ==1)
	{
		printf("\nC :> RCPT TO : <%s>\n",receivor);
	    send(client_fd,"Receivor Ok....",sizeof("Receivor Ok...."),0);
	}
	else
	{
		send(client_fd,"Invalid email id....",sizeof("Invalid email id...."),0);
		goto L2;
	}
	strcpy(msg,"");
	recv(client_fd,msg,1024,0);

	if(strcmp("DATA",msg)==0)
	{
		printf("\nC :> DATA: \n");
		send(client_fd,"Send the email....(to end the email put :) at a new line...",sizeof("Send the email....(to end the email put :) at the end..."),0);

	}

	strcpy(buffer,"");
	strcpy(msg,"");
	recv(client_fd,buffer,sizeof(char)*1024,0);
	printf("\n-----------------------------------------------\n");
	printf("%s",buffer);
	printf("\n-----------------------------------------------\n");
	recv(client_fd,msg,1024,0);
	if(strcmp("QUIT",msg)==0)
	{
		send(client_fd,"Closing Connection....",sizeof("Closing Connection...."),0);
		printf("\nClosing Connection....\n");
		close(client_fd);
	}
}




