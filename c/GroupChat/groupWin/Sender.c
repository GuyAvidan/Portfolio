#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#define PID_LEN 20
char *colors_text[7]={"\033[0;30m" "\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m", "\033[0;35m","\033[0;36m", "\033[0;37m"};

int main(int argc, char* argv[])
{
    size_t sender=getpid();
    FILE *SenderPID_FILE = fopen("Sender.txt", "w");
    int sock=0, sent_bytes;
    struct sockaddr_in sin;
    struct sockaddr_in mcast_group;
    char buffer[100], massege[100];
    char *color;
    if (SenderPID_FILE == NULL)
    {
        perror("file open failed");
        return;
    }
    srand(time(NULL));
    color=colors_text[rand()%7];
    fprintf(SenderPID_FILE, "%ld", sender);
    fclose(SenderPID_FILE);
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) 
    {
        perror("socket failed");
        close(sock);
    }
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(argv[1]);
    sin.sin_port = htons(atoi(argv[2]));
    while (1)
    {
        printf("Enter massege:\n");
        fgets(buffer, 200, stdin);
        strcpy(massege,color);
        strcat(massege,argv[3]);
        strcat(massege,": ");
        strcat(massege,buffer);
        sent_bytes = sendto(sock, massege, strlen(massege), 0,(struct sockaddr *) &sin, sizeof(sin));
        if (sent_bytes < 0) 
        {
            perror("sendto failed");
            close(sock);
        }
        
    } 
}

