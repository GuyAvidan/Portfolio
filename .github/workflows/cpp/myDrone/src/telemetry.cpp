#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include "telemetry.hpp"

static float distance( float x1,float x2, float y1,float y2, float z1,float z2);

Telemetry::Telemetry(float a_batteryStatus,float a_engineTemperature, float a_height,
    float a_xCoordinate, float a_yCoordinate)
:   m_batteryStatus(a_batteryStatus)
,   m_engineTemperature(a_engineTemperature)
,   m_height(a_height)
,   m_xCoordinate(a_xCoordinate)
,   m_yCoordinate(a_yCoordinate)
{
    m_distanceFromOperator = distance(m_xCoordinate, 0, m_yCoordinate, 0, m_height, 0);
}

Telemetry::Telemetry( std::string a_data)
{
    std::stringstream stream(a_data);
    std::vector<std::string> tokens;
    std::string token;
    while (stream >> token)
    {
        tokens.push_back(token);
    }
    m_batteryStatus = stof(tokens[0]);
    m_engineTemperature = stof(tokens[1]);
    m_height = stof(tokens[2]);
    m_xCoordinate = stof(tokens[3]);
    m_yCoordinate = stof(tokens[4]);
    m_distanceFromOperator = stof(tokens[5]);

}

void Telemetry::SetHeight(float a_change)
{
    m_height += a_change;
    if(m_height<0)
        m_height=0;
    m_distanceFromOperator = distance(m_xCoordinate, 0, m_yCoordinate, 0, m_height, 0);
}

void Telemetry::SetXCoordinate(float a_change)
{
    m_xCoordinate += a_change;
    m_distanceFromOperator = distance(m_xCoordinate, 0, m_yCoordinate, 0, m_height, 0);
}

void Telemetry::SetYCoordinate(float a_change)
{
    m_yCoordinate += a_change;
    m_distanceFromOperator = distance(m_xCoordinate, 0, m_yCoordinate, 0, m_height, 0);
}

void Telemetry::FreeFall()
{
    m_engineTemperature = 25.0;
    m_height = 0;
    m_distanceFromOperator = distance(m_xCoordinate, 0, m_yCoordinate, 0, m_height, 0);

}

std::string Telemetry::ToString() const
{
    std::stringstream stream;
    stream << m_batteryStatus << " " << m_engineTemperature << " " << m_height<< " ";
    stream << m_xCoordinate<< " " << m_yCoordinate << " " << m_distanceFromOperator;
    return stream.str();
}
void Telemetry::Print()
{
    std::cout << "Drone status: \n";
    std::cout << "Coordinate (X,Y,H): " << m_xCoordinate<< "m'" << m_yCoordinate; 
    std::cout<< "m'"<< m_height <<"m"<<std::endl;
    std::cout << "Distance from operator; " << m_distanceFromOperator<< "m" << std::endl;
    std::cout << "Battery status: " << m_batteryStatus<< "%"<< std::endl;
    std::cout << "Engine temperature: " << m_engineTemperature << "°C"<< std::endl;
}

static float distance( float x1,float x2, float y1,float y2, float z1,float z2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2) * 1.0);
}