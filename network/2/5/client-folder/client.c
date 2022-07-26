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
	
	
	system("ls > /home/user/Desktop/network/2/5/ls_client.txt");
	while(1)
	{
		printf("\nEnter \n1. get file\n2. put file\n3. close\n->");
		int n;
		scanf("%d",&n);
		switch(n)
		{
			case 1:
				{
					int i=1;
					send(server_fd,&i,sizeof(int),0);
					char f[50];
					FILE *fp;
					fp=fopen("/home/user/Desktop/network/2/5/ls_server.txt","r");
					while(!feof(fp))
					{
							char msg[50];
						fscanf(fp,"%s",msg);
						printf("%s\n",msg);
					}
					fclose(fp); 
					printf("\nEnter the file name: ");
					scanf(" %s",f);
					printf("%s",f);
					int p=0;
					fp=fopen("/home/user/Desktop/network/2/5/ls_server.txt","r");
					while(!feof(fp))
					{
						char msg[50];
						fscanf(fp,"%s",msg);
						if(strcmp(msg,f)==0)
						{
							p=1;
							break;
						}
					}
					fclose(fp);
					if(p==1)
					{
						FILE *fp2;
						char b[50];
						snprintf(b,1024,"" " > %s",f);
						system(b);
						send(server_fd,f,sizeof(f),0);
						fp2=fopen(f,"w");
						char arr[50];
						recv(server_fd,arr,1024,0);
						while(strcmp(arr,":)")!=0)
						{
							fprintf(fp2,"%s",arr);
							strcpy(arr,"");
							recv(server_fd,arr,1024,0);
						}
						fclose(fp2);
					}
					else
					{
						printf("\nFile Not Found......");
					}

				}
		}
	}
	
}
	
