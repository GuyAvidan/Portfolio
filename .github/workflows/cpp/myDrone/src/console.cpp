#include <vector>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <iostream>

#include "server.hpp"
#include "console.hpp"
#include "protocol.hpp"
#include "telemetry.hpp"

Console::Console()
:   m_msgSocket("127.0.0.1",1990)
{}

void Console::TurnOn()
{
    m_active = true;
    std::cout<< "connection status:" << m_msgSocket.Connect() << std::endl;
}

void Console::Move(Direction a_direction)
{
    char bufferSend[1028];
    m_messageProtocol.PackMove(a_direction, bufferSend);
    m_msgSocket.SendFunc(bufferSend);
}

void Console::DroneStatus()
{
    char bufferSend[1028];
    m_messageProtocol.PackAskForStatus(bufferSend);
    m_msgSocket.SendFunc(bufferSend);
    char packet[1028];
    m_msgSocket.RecvFunc(packet);
    Telemetry telemetry;
    m_messageProtocol.UnPackStatus(telemetry, packet);
    telemetry.Print();
}

void Console::Shutdown()
{
    m_active = false;

}
    