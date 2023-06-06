#include <iostream>
#include <string>
#include "mu_test.h"
#include <chrono>
#include <thread>

#include "drone.hpp"
#include "console.hpp"
#include "protocol.hpp"
#include "server.hpp"
#include "client.hpp"
#include "telemetry.hpp"


BEGIN_TEST(server_client_test)
    Server server("127.0.0.1",1990);
    std::cout<< server.Connect()<<'\n';
    server.SendFunc("welcome from server");
    //char buf[1024];
    //server.RecvFunc(buf);
    //std::cout<< buf<<std::endl;
    ASSERT_PASS();
END_TEST

BEGIN_TEST(telemetry_test)
    Telemetry telemetry;
    telemetry.Print();
    telemetry.SetHeight(10);
    telemetry.SetXCoordinate(1);
    telemetry.SetXCoordinate(3);
    telemetry.m_batteryStatus -= 5;
    telemetry.Print();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(Console_connect_to_Drone_test)
    Console console;
    console.TurnOn();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(Console_Move_test)
    Console console;
    console.TurnOn();
    for(int i = 0; i < 10;++i)
    {
        console.Move(Direction::UP);
    }
    for(int i = 0; i < 15;++i)
    {
        console.Move(Direction::RIGHT);
    }
    for(int i = 0; i < 5;++i)
    {
        console.Move(Direction::FRONT);
    }
    ASSERT_PASS();
END_TEST

BEGIN_TEST(Console_Ask_telemetry_test)
    Console console;
    console.TurnOn();
    for(int i = 0; i < 10;++i)
    {
        console.Move(Direction::UP);
    }
    console.DroneStatus();
    ASSERT_PASS();
END_TEST

TEST_SUITE([Drone Tests])
    TEST(server_client_test)
    IGNORE_TEST(telemetry_test)
    IGNORE_TEST(Console_connect_to_Drone_test)
    IGNORE_TEST(Console_Move_test)
    IGNORE_TEST(Console_Ask_telemetry_test)
END_SUITE
