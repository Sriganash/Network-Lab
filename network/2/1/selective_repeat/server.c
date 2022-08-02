#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#define port 8080

int frames[10];
static int q = 0;
static int l = 0;

int sockfd, clientfd;
struct sockaddr_in server, client;
int addrlen;

pthread_t t;


int receiveEntireWindow(int frameSize)
{
    
    return 1;
}

int input()
{
    char ch[5];
    printf("Enter ACK or NAK for the FRAME %d\n", frames[l]);
    scanf(" %s", ch);
    if(strcmp(ch,"ACK")==0)
        return 1;
    else
        return 0;
}

void *receiveAndAcknowledge()
{

    char msg[100];
    char ack[100];
    char nak[100];
    char temp[100];

    int windowSize;
    recv(clientfd, msg, sizeof(char) * 50, 0);
    windowSize = atoi(msg);

    strcpy(ack, "ACK");
    strcpy(nak, "NAK");

    int flag = 0;
    int nakFlag = 0;
    while (1)
    {
        msg[0] = '\0';

        if (!flag)
        {
            char *msg = (char *)malloc(sizeof(char) * 10);
        for (int p = 0; p < windowSize; p++)
        {
            msg[0] = '\0';
            recv(clientfd, msg, sizeof(char) * 10, 0);
            if (msg[0] != '\0')
            {
                printf("Received frame: %s\n", msg);
                frames[q++] = atoi(msg);
            }
            else
            {
                exit(EXIT_SUCCESS);
            }
        }
            flag = 1;
        }
        else
        {
            char *msg = (char *)malloc(sizeof(char) * 10);
        for (int p = 0; p < 1; p++)
        {
            msg[0] = '\0';
            recv(clientfd, msg, sizeof(char) * 10, 0);
            if (msg[0] != '\0')
            {
                printf("Received frame: %s\n", msg);
                frames[q++] = atoi(msg);
            }
            else
            {
                exit(EXIT_SUCCESS);
            }
        }
        }

        if (input())
        { // ACK
            strcpy(ack, "ACK-");
            sprintf(temp, "%d", frames[l++]);
            strcat(ack, temp);
            send(clientfd, ack, sizeof(char) * strlen(ack), 0);
            nakFlag = 0;
        }
        else
        { // NAK
            strcpy(nak, "NAK-");
            sprintf(temp, "%d", frames[l]);
            strcat(nak, temp);
            send(clientfd, nak, sizeof(char) * strlen(nak), 0);
            nakFlag = 1;

            while (1)
            {
                recv(clientfd, msg, sizeof(char) * 10, 0);
                if (!input())
                {
                    strcpy(nak, "NAK-");
                    sprintf(temp, "%d", frames[l]); // msg=frames[l]
                    strcat(nak, temp);
                    send(clientfd, nak, sizeof(char) * strlen(nak), 0);
                }
                else
                {
                    strcpy(ack, "ACK-");
                    sprintf(temp, "%d", frames[l++]);
                    strcat(ack, temp);
                    send(clientfd, ack, sizeof(char) * strlen(ack), 0);
                    break;
                }
            }
        }

        sleep(1);
    }
}

void main()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    addrlen = sizeof(server);

    if (bind(sockfd, (struct sockaddr *)&server, (socklen_t)addrlen) < 0)
    {
        perror("Binded Unsuccessful\n");
        exit(EXIT_FAILURE);
    }
    printf("Bind success\n");

    listen(sockfd, 5);
    clientfd = accept(sockfd, (struct sockaddr *)&client, (socklen_t *)&addrlen);
    if (clientfd < 0)
    {
        perror("Client Accept unsuccessfull\n");
        exit(EXIT_FAILURE);
    }
    printf("Client accepted successfully\n");

    pthread_create(&t, NULL, receiveAndAcknowledge, NULL);
    pthread_join(t, NULL);
}
