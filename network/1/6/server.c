#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

	int sockfd;
int i;
int clientfd[5];

int chopstick[5];
int n;
void wait(int s)
{
	while(chopstick[s]<=0);
	chopstick[s]=0;
}

void signal(int s)
{
	chopstick[s]++;
}
void *phil(void *p)
{
	int i=*(int *)p;
	printf("\n%d",i);
	printf("\nphilosopher %d thinking ..........",i+1);
	wait(i);
	wait((i+1)%n);
	sleep(2);
	printf("\nphilosopher %d finished eating ..........",i+1);
	signal(i);
	signal((i+1)%n);
	
}
void *listenAccept(void * arg)
{
	while(1)
	{
		clientfd[i]=accept(sockfd,(struct sockaddr*)NULL,(socklen_t *)NULL);

		pthread_t t;
		pthread_create(&t,NULL,phil,(void *)&clientfd[i]);

		pthread_join(t,NULL);
		pthread_mutex_lock(&lock);
		i++;
		pthread_mutex_unlock(&lock);
	}
}

void main()
{
	struct sockaddr_in server,client;


	n=5;
	for(int i=0;i<n;i++)
		chopstick[i]=1;
	i=0;
	int opt;
	int c=sizeof(struct sockaddr);

	sockfd=socket(AF_INET,SOCK_STREAM,0);

	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(8080);

	bind(sockfd,(struct sockaddr*)&server,sizeof(server));

	listen(sockfd,5);

	pthread_t t1;
	pthread_create(&t1,NULL,listenAccept,NULL);
	pthread_join(t1,NULL);

}