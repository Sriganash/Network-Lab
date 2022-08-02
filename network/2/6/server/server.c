// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<pthread.h>
#define PORT 8080

static int server_fd;
int clientfd[100]={-1};
struct sockaddr_in server;
static int clientCount=0;

pthread_mutex_t lock =PTHREAD_MUTEX_INITIALIZER;

void* readMessage(void * arg)
{
	int client=*(int*)arg;
system("ls > /home/user/Desktop/network/2/6/sls_server.txt");

  char filename[50];
  recv(client,filename,1024,0);

  FILE *fp;
  fp=fopen(filename,"r");
  char msg[500];
  while(fgets(msg,500,fp)!=NULL)
  {
    printf("%s",msg);
    sleep(1);
    send(client,msg,sizeof(msg),0);
  }
  int ret = 42;
   pthread_exit(&ret);
}

void * listenAccept(void *arg){
     while (1){
        clientfd[clientCount]=accept(server_fd,(struct sockaddr*)NULL,(socklen_t *)NULL);
        if (clientfd[clientCount]<0){
            printf("\nAccept failed!!\n");
        }
        else{
            printf("\nAccept success\n");
            pthread_t t;
            int c=clientfd[clientCount];
            pthread_create(&t,NULL,readMessage,(void *)&c);
            
            pthread_mutex_lock(&lock);
            clientCount++;
            pthread_mutex_unlock(&lock);
            void *status;

            pthread_join(t,&status);
            printf("%d",*(int*)status);


        }
    }
}

void main()
{
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024];
	char* hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))== 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	listen(server_fd,10);

    pthread_t t1;
    pthread_create(&t1,NULL,listenAccept,NULL);   
    pthread_join(t1,NULL);

    close(server_fd);

}
