#pragma once
#include "ISensor.h"
#include <string>
#include <windows.h>

namespace AgroResQ
{
    namespace Hardware
    {
        class RealSensor : public ISensor
        {
        private:
            std::string port;
            HANDLE hSerial;
            bool connected;
            std::string lastData;

            bool openPort();
            void closePort();
            std::string readLine();
            bool parseData(const std::string& data, double& moisture, double& ph, double& temp, double& humidity);

        public:
            RealSensor(const std::string& port = "COM3");
            ~RealSensor();

            double readMoisture() override;
            double readPH() override;
            double readTemperature() override;
            double readHumidity() override;
            bool isConnected() override;
            std::string getSensorName() const override;
            void setPort(const std::string& port);
        };
    }
}