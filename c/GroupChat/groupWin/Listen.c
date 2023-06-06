#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h> 
#include <sys/socket.h>
#define PID_LEN 20
#define FAIL 0
#define OK 1
#define DATA_LEN 100

int main(int argc, char* argv[])
{
    size_t listen=getpid();
    int listenSock, optval = 1,read_bytes;
    FILE *ListenPID_FILE = fopen("Listen.txt", "w");
    struct sockaddr_in sinGroup;
    struct ip_mreq mreq;
    char str[PID_LEN];
    char buffer[DATA_LEN];
    unsigned int sin_len=sizeof(sinGroup);
    if (ListenPID_FILE == NULL)
    {
        perror("file open failed");
        return FAIL;
    }
    
    fprintf(ListenPID_FILE, "%ld", listen);
    fclose(ListenPID_FILE);
    if ( (listenSock=socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        perror("socket failed");
        close(listenSock);
        return FAIL;
    }
    
    memset(&sinGroup, 0, sizeof(sinGroup));
    sinGroup.sin_family = AF_INET;
    sinGroup.sin_port = htons(atoi(argv[2]));
    sinGroup.sin_addr.s_addr = inet_addr(argv[1]);
    if (setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) 
    {
        perror("reuse failed");
        close(listenSock);
        return FAIL;
    }
    if (bind(listenSock, (struct sockaddr *) &sinGroup, sizeof(sinGroup)) < 0) 
    {
        perror("bind failed");
        close(listenSock);
        return FAIL;
    }
    mreq.imr_multiaddr = sinGroup.sin_addr;
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(listenSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        perror("joined failed");
        close(listenSock);
        return FAIL;
    } 
    printf("Group Chat\n");
    while (1)
    {
        read_bytes = recvfrom(listenSock, buffer, sizeof(buffer), 0,(struct sockaddr *) &sinGroup, &sin_len);
        if (read_bytes < 0) 
        {
            perror("recvfrom failed");
            close(listenSock);
            return FAIL;
        }
        buffer[read_bytes] = '\0';
        printf("%s", buffer);
        fflush(stdout);
    }
    
    
}