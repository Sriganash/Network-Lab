// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
  int server_fd = 0, valread;
  struct sockaddr_in serv_addr;
  char* hello = "Hello from client";
  char buffer[1024];
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary
  // form
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
    <= 0) {
    printf(
      "\nInvalid address/ Address not supported \n");
    return -1;
  }

  if (connect(server_fd, (struct sockaddr*)&serv_addr,
        sizeof(serv_addr))
    < 0) {
    printf("\nConnection Failed \n");
    return -1;
  }
  /*send(sock, hello, strlen(hello), 0);
  printf("Hello message sent\n");
  valread = read(sock, buffer, 1024);
  printf("%s\n", buffer);
  return 0;
  */
  printf("\nThe files in server folder are: ");
  printf("\n==================================\n");
  sleep(1);
  system("cat /home/user/Desktop/network/2/ls_server.txt");

  printf("\nEnter the filename to download: ");
  char filename[50];
  scanf(" %s",filename);

  send(server_fd,filename,sizeof(filename),0);
  FILE *fp;
  fp=fopen(filename,"w");
  char msg[500];
  while(1)
  {
    int n=recv(server_fd,msg,2048,0);
    if(n<=0)
      break;
    else
    {
      fprintf(fp,"%s",msg);

    }
  }
  fclose(fp);
  printf("\nFile was received...");
  printf("\nDo you wish to see the file?(y/n) ");
  char c;
  scanf(" %c",&c);
  if(c=='y')
  {
    sleep(2);
    printf("\n==================================\n");
    snprintf(buffer,1024,"cat %s",filename);
    system(buffer);
    printf("\n==================================\n");
   }

}
