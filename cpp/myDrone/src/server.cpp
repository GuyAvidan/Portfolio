#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <sys/select.h>
#include <chrono>
#include <thread>

#include "protocol.hpp"
#include "server.hpp"

Server::Server(std::string a_IP, size_t a_port)
:   m_IP(a_IP)
,   m_port(a_port)
,   m_socket(0)
,   m_clientSocket(0)
,   m_connected(false)
{}

Server::~Server()
{
    close(m_socket);
    close(m_clientSocket);
}

bool Server::Connect()
{
    socklen_t clientLen;
    struct sockaddr_in serv_addr, cli_addr;
    m_socket =  socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) 
    throw std::runtime_error("ERROR opening socket.\n");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_addr.s_addr = INADDR_ANY;  
    serv_addr.sin_port = htons(m_port);
    int optval = 0;
    if(setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR,&optval, sizeof(optval)) < 0) 
    {
        close(m_socket);
        throw std::runtime_error("ERROR on setsockopt.\n");
    }
    setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR,&optval,sizeof(optval));
    if (bind(m_socket, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
        close(m_socket);
        throw std::runtime_error("ERROR on binding.\n");
    }
    listen(m_socket,5);
    clientLen = sizeof(cli_addr);
    m_clientSocket = accept(m_socket, (struct sockaddr *) &cli_addr, &clientLen);
    if (m_clientSocket < 0) 
    {
        close(m_socket);
        throw std::runtime_error("ERROR on accept.\n");
    }
    std::cout<< "server: got connection";
    m_connected = true;
    return true; 
}

ssize_t Server::RecvFunc(char *a_packet)
{
    ssize_t read_bytes;
    if(a_packet == NULL)
    {
        return -1;
    }
    
    read_bytes = recv(m_clientSocket, a_packet, m_bufferSize, 0);
    if (read_bytes <= 0)
    {
        close(m_clientSocket);
        throw std::runtime_error("ERROR on receive.\n");
    }else{
        a_packet[read_bytes] = '\0';
        return read_bytes;
    }
}

bool Server::SendFunc(std::string a_buffer)
{
    int sent_bytes;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    sent_bytes = send(m_clientSocket, a_buffer.c_str(), a_buffer.size(), 0);

    if (sent_bytes <= 0)
    {
        close(m_clientSocket);
        throw std::runtime_error("ERROR on send.\n");
    }
    return true;
}

