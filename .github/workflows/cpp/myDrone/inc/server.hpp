#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/select.h>
#include <string>

class Server
{
public:
    Server(std::string a_IP, size_t a_port);
    ~Server();

    bool Connect();
    ssize_t RecvFunc(char *a_packet);
    bool SendFunc(std::string a_buffer);
private:
    std::string m_IP;
    size_t m_port;
    int m_socket;
    int m_clientSocket;
    size_t m_bufferSize = 1024;
    int m_listenSocket;
    bool m_flagPause;
    int m_activity;
    bool m_connected;

};

#endif