#pragma once
#include <string>

namespace AgroResQ
{
    namespace Hardware
    {
        class ISensor
        {
        public:
            virtual ~ISensor() = default;

            virtual double readMoisture() = 0;
            virtual double readPH() = 0;
            virtual double readTemperature() = 0;
            virtual double readHumidity() = 0;
            virtual bool isConnected() = 0;
            virtual std::string getSensorName() const = 0;
        };
    }
}