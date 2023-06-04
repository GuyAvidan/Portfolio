#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "server.hpp"
#include "protocol.hpp"

class Console
{
public:
    Console();
    ~Console() = default;
    Console(const Console& other) = delete;
    Console(const Console&& other) = delete;

    void TurnOn();
    void Shutdown();
    void Move(Direction a_direction);
    //void RecordVideo();
    //void StopRecordVideo();
    void DroneStatus();
    //bool SendMsg(Message a_msg);
    //Message ReceiveMsg();
    //void ControlBattery();
    bool makeMsg(Tag a_tag, char *a_massage, size_t a_massageLength);

private:

private:
    /*
    bool m_shutdown = false;
    std::thread m_batteryThread;
    mutable std::shared_mutex m_batteryMutexes; */
    
    Server m_msgSocket;
    bool m_active = false;
    Protocol m_messageProtocol;
};

#endif