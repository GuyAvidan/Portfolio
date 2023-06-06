#include "drone.hpp"
#include "telemetry.hpp"
#include "client.hpp"
#include "protocol.hpp"

#include <iostream>

Drone::Drone()
:   m_msgSocket("127.0.0.1",1990)
,   m_telemetrySocket("127.0.0.1",1991)
{
}

Drone::~Drone()
{
    if(!m_shutdown)
        Shutdown();
}

void Drone::Shutdown()
{
    m_active = false;
    m_telemetry.FreeFall();
    m_batteryThread.join();
    m_listenThread.join();
    m_shutdown = true;
}

void Drone::Move(Direction a_direction)
{
    if(m_active)
    {
        if (a_direction == Direction::FRONT)
            m_telemetry.SetXCoordinate(0.05);
        else if (a_direction == Direction::BACK)
            m_telemetry.SetXCoordinate(-0.05);
        else if (a_direction == Direction::LEFT)
            m_telemetry.SetYCoordinate(-0.05);
        else if (a_direction == Direction::RIGHT)
            m_telemetry.SetYCoordinate(0.05);
        else if (a_direction == Direction::UP)
            m_telemetry.SetHeight(0.05);
        else if (a_direction == Direction::DOWN)
            m_telemetry.SetHeight(-0.05);
        m_move++;
    }
    
}

void Drone::TurnOn()
{
    m_active = true;
    std::cout<< "connection status:" << m_msgSocket.Connect() << std::endl;
    m_batteryThread = std::move(std::thread(&Drone::ControlBattery, this));
    m_listenThread = std::move(std::thread(&Drone::Listen, this));

}
//void RecordVideo();
//void StopRecordVideo();
Telemetry Drone::DroneStatus()
{
    std::shared_lock lock(m_batteryMutexes);
    return m_telemetry;
}

void Drone::ControlBattery()
{
    while(m_active)
    {
        {   
            std::unique_lock lock(m_batteryMutexes);
            if (m_telemetry.m_batteryStatus <=  0 || m_telemetry.m_engineTemperature >= 40)
            {
                m_active = false;
                break;
            }
            sleep(1);
            m_telemetry.m_batteryStatus -= 0.01;
            m_telemetry.m_engineTemperature += 0.01;
            while (m_move != 0)
            {
                m_telemetry.m_batteryStatus -= 0.05;
                m_telemetry.m_engineTemperature += 0.01;
                m_move--;
            }
            if (m_telemetry.m_batteryStatus <=  0 || m_telemetry.m_engineTemperature >= 40)
            {
                m_active = false;
            }
            
        }
    }
    m_telemetry.FreeFall();
}

void Drone::Listen()
{
    while(m_active)
    {
        recvMsg();
    }
}
//bool SendMsg(Message a_msg);
//Message ReceiveMsg();

/* bool Drone::makeMsg(Tag a_tag, char *a_massage, size_t a_massageLength)
{
    ssize_t sent_bytes;
    char packet[1024];
    if( a_tag == Tag::MOVE)
    {
        if ((m_messageProtocol.PackMoveRequest(a_massage, Packet)))
        {
            return CLIENT_PACKING_ERROR;
        }
        SendFunc(_myClientMan->m_clientNet, Packet);

    } else if( a_tag == Tag::STATUS)
    {

    }
} */

void Drone::recvMsg()
{
    Tag tag;
    char packet[1024];
    ssize_t msgLen;
    msgLen = m_msgSocket.RecvFunc(packet);
    if(msgLen < 1)
        return;
    tag = m_messageProtocol.GetTag(packet);
    if( tag == Tag::MOVE)
    {
        Direction direction;
        m_messageProtocol.UnPackMoveOrder(packet, direction);
        Move(direction);
    } else if( tag == Tag::STATUS)
    {
        m_messageProtocol.PackStatus( m_telemetry , packet);
        m_msgSocket.SendFunc(packet);
    }
}