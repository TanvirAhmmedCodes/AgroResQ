#include "RealSensor.h"
#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace AgroResQ
{
    namespace Hardware
    {
        RealSensor::RealSensor(const std::string& port)
            : port(port), connected(false)
        {
            openPort();
        }

        RealSensor::~RealSensor()
        {
            closePort();
        }

        bool RealSensor::openPort()
        {
            serialPort.open(port);
            if (!serialPort.is_open())
            {
                connected = false;
                return false;
            }

            #ifdef _WIN32
            Sleep(2000);
            #else
            sleep(2);
            #endif

            connected = true;
            return true;
        }

        void RealSensor::closePort()
        {
            if (serialPort.is_open())
            {
                serialPort.close();
            }
            connected = false;
        }

        std::string RealSensor::readLine()
        {
            std::string line;
            if (serialPort.is_open() && std::getline(serialPort, line))
            {
                return line;
            }
            return "";
        }

        bool RealSensor::parseData(const std::string& data, double& moisture, double& ph, double& temp, double& humidity)
        {
            std::stringstream ss(data);
            std::string token;
            int count = 0;

            while (std::getline(ss, token, ','))
            {
                try
                {
                    double value = std::stod(token);
                    switch (count)
                    {
                        case 0: moisture = value; break;
                        case 1: ph = value; break;
                        case 2: temp = value; break;
                        case 3: humidity = value; break;
                    }
                    count++;
                }
                catch (...)
                {
                    return false;
                }
            }

            return count == 4;
        }

        double RealSensor::readMoisture()
        {
            if (!connected) return -1.0;

            double moisture, ph, temp, humidity;
            std::string data = readLine();

            if (!data.empty() && parseData(data, moisture, ph, temp, humidity))
            {
                lastData = data;
                return moisture;
            }

            return -1.0;
        }

        double RealSensor::readPH()
        {
            if (!connected) return -1.0;

            double moisture, ph, temp, humidity;
            std::string data = readLine();

            if (!data.empty() && parseData(data, moisture, ph, temp, humidity))
            {
                lastData = data;
                return ph;
            }

            return -1.0;
        }

        double RealSensor::readTemperature()
        {
            if (!connected) return -1.0;

            double moisture, ph, temp, humidity;
            std::string data = readLine();

            if (!data.empty() && parseData(data, moisture, ph, temp, humidity))
            {
                lastData = data;
                return temp;
            }

            return -1.0;
        }

        double RealSensor::readHumidity()
        {
            if (!connected) return -1.0;

            double moisture, ph, temp, humidity;
            std::string data = readLine();

            if (!data.empty() && parseData(data, moisture, ph, temp, humidity))
            {
                lastData = data;
                return humidity;
            }

            return -1.0;
        }

        bool RealSensor::isConnected()
        {
            if (!connected)
            {
                openPort();
            }
            return connected;
        }

        std::string RealSensor::getSensorName() const
        {
            return "Real Arduino Sensor (" + port + ")";
        }

        void RealSensor::setPort(const std::string& port)
        {
            if (connected)
            {
                closePort();
            }
            this->port = port;
            openPort();
        }
    }
}