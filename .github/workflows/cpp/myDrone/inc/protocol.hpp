#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <iostream>

#include "telemetry.hpp"

enum class Direction:char {RIGHT = 'r', LEFT = 'l', FRONT = 'f', BACK = 'b', UP = 'u', DOWN = 'd'};

enum class Tag:char
{
    MOVE = 'm', 
    STATUS = 's'
};

class Protocol
{
public:
    Protocol(/* args */){};
    ~Protocol(){};
    Tag GetTag(char *a_packet);

    ssize_t PackMove(Direction &a_direction, char *bufferSend);
    ssize_t PackAskForStatus(char *bufferSend);
    ssize_t PackStatus(Telemetry &a_telemetry, char *bufferSend);
    void UnPackMoveOrder(char *a_packet, Direction &a_direction);
    void UnPackStatus(Telemetry &a_telemetry, char *bufferSend);

public:
    size_t m_packetSize = 1024;
};


#endif