#include "RealSensor.h"
#include <windows.h>
#include <iostream>
#include <sstream>

namespace AgroResQ
{
    namespace Hardware
    {
        RealSensor::RealSensor(const std::string& port)
            : port(port), connected(false), hSerial(INVALID_HANDLE_VALUE)
        {
            openPort();
        }

        RealSensor::~RealSensor()
        {
            closePort();
        }

        bool RealSensor::openPort()
        {
            std::string fullPort = "\\\\.\\" + port;
            
            hSerial = CreateFileA(
                fullPort.c_str(),
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );

            if (hSerial == INVALID_HANDLE_VALUE)
            {
                std::cerr << "[RealSensor] Failed to open port: " << port << "\n";
                connected = false;
                return false;
            }

            DCB dcbSerialParams = {0};
            dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
            
            if (!GetCommState(hSerial, &dcbSerialParams))
            {
                std::cerr << "[RealSensor] Failed to get comm state\n";
                CloseHandle(hSerial);
                hSerial = INVALID_HANDLE_VALUE;
                connected = false;
                return false;
            }

            dcbSerialParams.BaudRate = CBR_115200;
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;

            if (!SetCommState(hSerial, &dcbSerialParams))
            {
                std::cerr << "[RealSensor] Failed to set comm state\n";
                CloseHandle(hSerial);
                hSerial = INVALID_HANDLE_VALUE;
                connected = false;
                return false;
            }

            COMMTIMEOUTS timeouts = {0};
            timeouts.ReadIntervalTimeout = 50;
            timeouts.ReadTotalTimeoutConstant = 50;
            timeouts.ReadTotalTimeoutMultiplier = 10;
            SetCommTimeouts(hSerial, &timeouts);

            std::cout << "[RealSensor] ✅ Connected to " << port << " at 115200 baud\n";
            connected = true;
            return true;
        }

        void RealSensor::closePort()
        {
            if (hSerial != INVALID_HANDLE_VALUE)
            {
                CloseHandle(hSerial);
                hSerial = INVALID_HANDLE_VALUE;
            }
            connected = false;
        }

        std::string RealSensor::readLine()
        {
            if (hSerial == INVALID_HANDLE_VALUE) return "";

            char buffer[256];
            DWORD bytesRead;
            std::string line;
            
            while (true)
            {
                if (!ReadFile(hSerial, buffer, 1, &bytesRead, NULL) || bytesRead == 0)
                    break;
                
                if (buffer[0] == '\n')
                    break;
                if (buffer[0] != '\r')
                    line += buffer[0];
            }
            
            return line;
        }

        bool RealSensor::parseData(const std::string& data, double& moisture, double& ph, 
                                   double& temp, double& humidity)
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
            if (!connected) openPort();
            return connected;
        }

        std::string RealSensor::getSensorName() const
        {
            return "ESP32 AgroResQ Sensor (" + port + ")";
        }

        void RealSensor::setPort(const std::string& port)
        {
            if (connected) closePort();
            this->port = port;
            openPort();
        }
    }
}