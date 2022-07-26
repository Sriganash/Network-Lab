#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define port 8060

static int sockfd;
struct sockaddr_in server,client_addr;




void main(){

    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd==-1){
        perror("Socket creation failed!!\n");
        return;
    }
    else{
        printf("Socket created successfully\n");
    }

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(port);

    
    char msg[50];
    char job[50];
    int c=sizeof(struct sockaddr);
    L1:scanf(" %s",job);
    if(strcmp(job,"time")==0)
    {
        sendto(sockfd,job,sizeof(job),MSG_CONFIRM,(struct sockaddr*) &server,sizeof(server));
        recvfrom(sockfd,msg,1024,MSG_WAITALL,(struct sockaddr*) &client_addr,&c);
        printf("%s\n",msg);
        goto L1;
    }
    else
        goto L1;



}
