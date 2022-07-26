#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
        FILE *fp;
        char f[50];
        strcpy(f,"time");
        char text[50];
        sprintf(text, "%d", 4);
        strcat(f,text);
        strcat(f,".txt");
        fp=fopen(f,"w");
        char buffer[100];
        snprintf(buffer, 1000*sizeof(char), "date \"+%T\" > %s",f);
        system(buffer);

        fclose(fp);
        fp=fopen(f,"r");
        char msg[50];
        fscanf(fp,"%s",msg);
        printf("%s",msg);
}