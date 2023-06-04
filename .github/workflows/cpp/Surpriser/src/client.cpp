#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <thread>
#include <chrono>

#include "client.hpp"

Client::Client(std::string a_IP, size_t a_port)
:   m_IP(a_IP)
,   m_port(a_port)
,   m_socket(0)
,   m_connected(false)
{}

Client::~Client()
{
    close(m_socket);
}

bool Client::Connect()
{
    struct sockaddr_in sin;
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0)
    {
        close(m_socket);
        return false;
    }
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(m_IP.c_str());
    sin.sin_port = htons(m_port);
    if (connect(m_socket, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        close(m_socket);
        return false;
    }
    m_connected = true;
    return true;
}

ssize_t Client::RecvFunc(char *a_packet)
{
    ssize_t read_bytes;
    if(a_packet == NULL)
    {
        return -1;
    }
    read_bytes = recv(m_socket, a_packet, m_bufferSize, 0);
    if (read_bytes <= 0)
    {
        close(m_socket);
        //throw std::runtime_error("ERROR on receive.\n");
        return -1;
    }else{
        a_packet[read_bytes] = '\0';
        return read_bytes;
    }
}

/* bool Client::SendFunc(char* a_buffer, size_t a_bufferSize)
{
    int sent_bytes;
    sent_bytes = send(m_socket, a_buffer, a_bufferSize, 0);

    if (sent_bytes <= 0)
    {
        close(m_socket);
        throw std::runtime_error("ERROR on send.\n");
        return false;
    }
    return true;
} */

bool Client::SendFunc(std::string a_buffer)
{
    int sent_bytes;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    sent_bytes = send(m_socket, a_buffer.c_str(), a_buffer.size(), 0);

    if (sent_bytes <= 0)
    {
        close(m_socket);
        throw std::runtime_error("ERROR on send.\n");
    }
    return true;
}


int Client::GetSocket() const
{
    return m_socket;
}