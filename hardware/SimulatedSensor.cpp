#include "SimulatedSensor.h"

namespace AgroResQ
{
    namespace Hardware
    {
        SimulatedSensor::SimulatedSensor()
        {
            std::srand(static_cast<unsigned>(std::time(nullptr)));
            connected = true;
        }

        double SimulatedSensor::generateRandom(double min, double max)
        {
            double random = static_cast<double>(std::rand()) / RAND_MAX;
            return min + random * (max - min);
        }

        double SimulatedSensor::readMoisture()
        {
            return generateRandom(20.0, 80.0);
        }

        double SimulatedSensor::readPH()
        {
            return generateRandom(4.0, 9.0);
        }

        double SimulatedSensor::readTemperature()
        {
            return generateRandom(20.0, 40.0);
        }

        double SimulatedSensor::readHumidity()
        {
            return generateRandom(30.0, 90.0);
        }

        bool SimulatedSensor::isConnected()
        {
            return connected;
        }

        std::string SimulatedSensor::getSensorName() const
        {
            return "Simulated Sensor (Dummy Data)";
        }
    }
}