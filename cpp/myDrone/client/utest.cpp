#include <iostream>
#include <string>
#include "mu_test.h"

#include "drone.hpp"
#include "console.hpp"
#include "protocol.hpp"
#include "server.hpp"
#include "client.hpp"


BEGIN_TEST(server_client_test)
    Client client("127.0.0.1",1990);
    std::cout<< client.Connect()<< '\n';
    char buf[1024];
    client.RecvFunc(buf);
    std::cout<< buf<<std::endl;
    client.SendFunc(static_cast<char*>("Hi from client"));
    ASSERT_PASS();
END_TEST

BEGIN_TEST(Drone_create_test)
    Drone drone;
    drone.TurnOn();
    drone.DroneStatus();
    for(int i = 0; i < 60; ++i)
    {
        drone.Move(Direction::UP);
    }
    for(int i = 0; i < 20; ++i)
    {
        drone.Move(Direction::DOWN);
    }
    for(int i = 0; i < 50; ++i)
    {
        drone.Move(Direction::LEFT);
    }
    for(int i = 0; i < 30; ++i)
    {
        drone.Move(Direction::RIGHT);
    }
    for(int i = 0; i < 30; ++i)
    {
        drone.Move(Direction::FRONT);
    }
    for(int i = 0; i < 20; ++i)
    {
        drone.Move(Direction::BACK);
    }
    // x= 10 y = -20 z = 40 *0.05
    drone.DroneStatus().Print();

    ASSERT_PASS();
END_TEST

BEGIN_TEST(Telemetry_to_string_test)
    Drone drone;
    drone.TurnOn();
    drone.DroneStatus();
    for(int i = 0; i < 60; ++i)
    {
        drone.Move(Direction::UP);
    }
    for(int i = 0; i < 20; ++i)
    {
        drone.Move(Direction::DOWN);
    }
    for(int i = 0; i < 50; ++i)
    {
        drone.Move(Direction::LEFT);
    }
    for(int i = 0; i < 30; ++i)
    {
        drone.Move(Direction::RIGHT);
    }
    for(int i = 0; i < 30; ++i)
    {
        drone.Move(Direction::FRONT);
    }
    for(int i = 0; i < 20; ++i)
    {
        drone.Move(Direction::BACK);
    }
    Telemetry  telem = drone.DroneStatus();
    std::string convert = telem.ToString();
    std::cout << convert << std::endl;
    ASSERT_PASS();
END_TEST

BEGIN_TEST(Telemetry_from_string_test)
    Telemetry  telem( 98, 27, 100, 5, 3);
    Telemetry telemDestination(telem.ToString());
    telemDestination.Print();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(Drone_shutdown_test)
    Drone drone;
    drone.TurnOn();
    drone.DroneStatus();
    for(int i = 0; i < 60; ++i)
    {
        drone.Move(Direction::UP);
    }
    for(int i = 0; i < 50; ++i)
    {
        drone.Move(Direction::LEFT);
    }
    for(int i = 0; i < 20; ++i)
    {
        drone.Move(Direction::BACK);
    }
    drone.DroneStatus().Print();
    drone.Shutdown();
    drone.DroneStatus().Print();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(Drone_temp_Fail_test)
    Drone drone;
    drone.TurnOn();
    drone.DroneStatus();
    for(int i = 0; i < 1600; ++i)
    {
        drone.Move(Direction::LEFT);
    }
    std::cout << 1501*0.05<<std::endl;
    drone.DroneStatus().Print();
    drone.Shutdown();
    drone.DroneStatus().Print();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(Drone_connect_to_console_test)
    Drone drone;
    drone.TurnOn();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(Drone_Move_from_console_test)
    Drone drone;
    drone.TurnOn();
    sleep(5);
    drone.DroneStatus().Print();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(Ask_telemetry_from_console_test)
    Drone drone;
    drone.TurnOn();
    sleep(5);
    drone.DroneStatus().Print();
    ASSERT_PASS();
END_TEST

TEST_SUITE([Drone Tests])
    IGNORE_TEST(server_client_test)
    IGNORE_TEST(Drone_create_test)
    IGNORE_TEST(Telemetry_to_string_test)
    IGNORE_TEST(Telemetry_from_string_test)
    IGNORE_TEST(Drone_shutdown_test)
    IGNORE_TEST(Drone_temp_Fail_test)
    IGNORE_TEST(Drone_connect_to_console_test)
    IGNORE_TEST(Drone_Move_from_console_test)
    TEST(Ask_telemetry_from_console_test)
END_SUITE
