#pragma once
#include "ISensor.h"
#include <cstdlib>
#include <ctime>

namespace AgroResQ
{
    namespace Hardware
    {
        class SimulatedSensor : public ISensor
        {
        private:
            bool connected;
            double generateRandom(double min, double max);

        public:
            SimulatedSensor();
            ~SimulatedSensor() = default;

            double readMoisture() override;
            double readPH() override;
            double readTemperature() override;
            double readHumidity() override;
            bool isConnected() override;
            std::string getSensorName() const override;
        };
    }
}