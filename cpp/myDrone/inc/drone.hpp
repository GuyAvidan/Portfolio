#ifndef DRONE_HPP
#define DRONE_HPP

#include <vector>
#include <thread>
#include <mutex>
#include <shared_mutex>

#include "telemetry.hpp"
#include "protocol.hpp"
#include "client.hpp"

class Drone
{
public:
    Drone();
    ~Drone();
    Drone(const Drone& other) = delete;
    Drone(const Drone&& other) = delete;

    void TurnOn();
    void Shutdown();
    void Move(Direction a_direction);
    //void RecordVideo();
    //void StopRecordVideo();
    Telemetry DroneStatus();
    //bool SendMsg(Message a_msg);
    void ControlBattery();
    bool makeMsg(Tag a_tag, char *a_massage, size_t a_massageLength);
    void recvMsg();

private:
    void Listen();


private:
    Telemetry m_telemetry;
    Protocol m_messageProtocol;
    bool m_active = false;
    bool m_shutdown = false;
    std::thread m_batteryThread;
    std::thread m_listenThread;
    mutable std::shared_mutex m_batteryMutexes;
    int m_move =0;
    Client m_msgSocket;
    Client m_telemetrySocket;

};

#endif