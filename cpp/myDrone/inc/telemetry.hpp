#ifndef TELEMETRY_HPP
#define TELEMETRY_HPP

#include <iostream>
#include <string>

struct Telemetry
{
    Telemetry(float a_batteryStatus = 100,float a_engineTemperature = 25.0, float a_height = 0,
        float a_xCoordinate = 0, float m_yCoordinate = 0);
    Telemetry( std::string a_data);
    ~Telemetry() = default;

    void SetHeight(float a_change);
    void SetXCoordinate(float a_change);
    void SetYCoordinate(float a_change);
    void FreeFall();
    std::string ToString() const;
    
    void Print();
public:
    float m_batteryStatus = 100.0;
    float m_engineTemperature = 25.0;
private:
    float m_height = 0;
    float m_xCoordinate = 0;
    float m_yCoordinate = 0;
    float m_distanceFromOperator = 0;

};

#endif