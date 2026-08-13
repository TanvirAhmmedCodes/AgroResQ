#pragma once
#include "ISensor.h"
#include "SimulatedSensor.h"
#include "RealSensor.h"
#include <memory>

namespace AgroResQ
{
    namespace Hardware
    {
        class SensorFactory
        {
        public:
            static std::shared_ptr<ISensor> createSensor(bool useReal = true, const std::string& port = "COM3");
        };
    }
}