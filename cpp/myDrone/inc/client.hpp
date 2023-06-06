#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
public:
    explicit Client(std::string a_IP, size_t a_port);
    ~Client();

    bool Connect();

    bool SendFunc(std::string a_buffer);
    ssize_t RecvFunc(char *a_packet);
    int GetSocket() const;
private:
    std::string m_IP;
    size_t m_port;
    int m_socket;
    bool m_connected;
    size_t m_bufferSize = 1024;
};


#endif