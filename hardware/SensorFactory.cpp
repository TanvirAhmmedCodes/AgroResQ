#include "SensorFactory.h"
#include <iostream>

namespace AgroResQ
{
    namespace Hardware
    {
        std::shared_ptr<ISensor> SensorFactory::createSensor(bool useReal, const std::string& port)
        {
            if (useReal)
            {
                try
                {
                    auto sensor = std::make_shared<RealSensor>(port);
                    if (sensor->isConnected())
                    {
                        std::cout << "[INFO] Connected to " << sensor->getSensorName() << "\n";
                        return sensor;
                    }
                    else
                    {
                        std::cout << "[WARNING] Failed to connect to real sensor. Switching to simulated mode.\n";
                    }
                }
                catch (...)
                {
                    std::cout << "[WARNING] Real sensor not found. Switching to simulated mode.\n";
                }
            }

            auto sensor = std::make_shared<SimulatedSensor>();
            std::cout << "[INFO] Using " << sensor->getSensorName() << "\n";
            return sensor;
        }
    }
}