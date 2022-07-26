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
struct sockaddr_in server;


void* receiveMsg(void * arg){                                                                                
    
    while (1){
	char *recmsg=(char *)malloc(sizeof(char)*100);
        recv(sockfd,recmsg,sizeof(char)*100,0);
        printf("%s\n",recmsg);
	strcpy(recmsg,"");
        fflush(stdout);
    }
}

void *sendMsg(void * arg){
    int flag=1;
    int started=0;

    char msg[100];

    while (1){
        if (!started){
            fflush(stdin);  fflush(stdout);
            printf(">>>:\n");
            scanf(" %s",msg);
            if (!strcmp(msg,"start")){
                started=1;
            }
            else{
                fflush(stdin);  fflush(stdout);
                printf("Enter a valid message!!\n");
            }
        }
        else{
            fflush(stdin);  fflush(stdout);
            printf(">>>:\n");
            scanf(" %s",msg);
            if (!strcmp(msg,"stop") && started){
                exit(0);
            }
            else{
                char smsgs[100];
                strcpy(smsgs,"Message from client: ");
                strcat(smsgs,msg);
                send(sockfd,smsgs,sizeof(char)*strlen(smsgs),0);          
            }
        }
    }
}   

void main(){

    sockfd=socket(AF_INET,SOCK_STREAM,0);
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

    if (connect(sockfd,(struct sockaddr*)&server,(socklen_t)sizeof(server))<0){
        perror("Connection failed!!\n");
    }
    printf("Connection success\n");

    pthread_t t1;
    pthread_create(&t1,NULL,receiveMsg,NULL);

    pthread_t t2;
    pthread_create(&t2,NULL,sendMsg,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}
