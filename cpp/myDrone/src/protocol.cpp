#include "protocol.hpp"

#include <iostream>

Tag Protocol::GetTag(char *a_packet)
{
    return static_cast<Tag>(a_packet[0]);
}

void Protocol::UnPackMoveOrder(char *a_packet, Direction &a_direction)
{
    a_direction = static_cast<Direction>(a_packet[1]);
}


void Protocol::UnPackStatus(Telemetry &a_telemetry, char *bufferSend)
{
    std::string status = bufferSend;
    Telemetry temp(status);
    a_telemetry = temp;

}

ssize_t Protocol::PackMove(Direction &a_direction, char *bufferSend)
{
    bufferSend[0] = static_cast<char>(Tag::MOVE);
    bufferSend[1] = static_cast<char>(a_direction);
    bufferSend[2] = '\0';
    return 3;
}

ssize_t Protocol::PackAskForStatus(char *bufferSend)
{
    bufferSend[0] = static_cast<char>(Tag::STATUS);
    bufferSend[1] = '\0';
    return 2;
}

ssize_t Protocol::PackStatus(Telemetry &a_telemetry, char *bufferSend)
{
    bufferSend[0] = static_cast<char>(Tag::STATUS);
    std::string status = a_telemetry.ToString();
    for(size_t i = 1; i < status.size(); ++i)
    {
        bufferSend[i] = static_cast<char>(status[i+1]);
    }
    bufferSend[status.size() +1] = '\0';
    return status.size()+1;
}

