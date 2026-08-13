#pragma once
#include "ISensor.h"
#include "SensorFactory.h"
#include <memory>

namespace AgroResQ
{
    namespace Hardware
    {
        struct SensorData
        {
            double moisture;
            double ph;
            double temperature;
            double humidity;
            bool valid;

            SensorData() : moisture(0), ph(0), temperature(0), humidity(0), valid(false) {}
        };

        class SensorService
        {
        private:
            std::shared_ptr<ISensor> sensor;

        public:
            SensorService(bool useReal = true, const std::string& port = "COM3");
            ~SensorService() = default;

            SensorData readAllData();
            double readMoisture();
            double readPH();
            double readTemperature();
            double readHumidity();
            bool isSensorConnected();
            void reconnect(bool useReal = true, const std::string& port = "COM3");
            std::string getSensorInfo() const;
        };
    }
}