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
int clientfd[100]={-1};
struct sockaddr_in server,client_addr;
static int clientCount=0;

pthread_mutex_t lock =PTHREAD_MUTEX_INITIALIZER;

void *show_Time(void *arg)
{
    int c=sizeof(struct sockaddr);
    char job[50];

    recvfrom(sockfd,job,1024,MSG_WAITALL,(struct sockaddr*) &client_addr,&c);
    while(strcmp(job,"time")==0)
    {
        char msg[50];
        strcpy(msg,"");
	
        FILE *fp;
        char f[50];
        strcpy(f,"time");
        char text[50];
        sprintf(text, "%d",sockfd);
        strcat(f,text);
        strcat(f,".txt");
        fp=fopen(f,"w");
        char buffer[100];
        snprintf(buffer, 1000*sizeof(char), "date \"+%T\" > %s",f);
        system(buffer);

        fclose(fp);
        fp=fopen(f,"r");
        fscanf(fp,"%s",msg);
        printf("%s\n",msg);
        sendto(sockfd,msg,sizeof(msg),MSG_CONFIRM,(struct sockaddr*) &client_addr,sizeof(client_addr));
        snprintf(buffer, 1000*sizeof(char), "rm %s",f);
        system(buffer);
        recvfrom(sockfd,msg,1024,MSG_WAITALL,(struct sockaddr*) &client_addr,&c);
    }
}


void main(void){
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd==-1){
        perror("Socket creation failed!!\n");
        return;
    }
    else{
        printf("Socket created successfully\n");
    }

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(port);

    if (bind(sockfd,(struct sockaddr*)&server,(socklen_t)sizeof(server))<0){
        perror("Bind failed!!\n");
        return;
    }
    printf("Bind successfull\n");
        

    pthread_t t1;
    pthread_create(&t1,NULL,show_Time,NULL); 
    pthread_join(t1,NULL);
    close(sockfd);
}

