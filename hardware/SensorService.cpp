#include "SensorService.h"

namespace AgroResQ
{
    namespace Hardware
    {
        SensorService::SensorService(bool useReal, const std::string& port)
        {
            sensor = SensorFactory::createSensor(useReal, port);
        }

        SensorData SensorService::readAllData()
        {
            SensorData data;
            
            if (!sensor->isConnected())
            {
                return data;
            }

            data.moisture = sensor->readMoisture();
            data.ph = sensor->readPH();
            data.temperature = sensor->readTemperature();
            data.humidity = sensor->readHumidity();

            if (data.moisture >= 0 && data.ph >= 0 && data.temperature >= 0 && data.humidity >= 0)
            {
                data.valid = true;
            }

            return data;
        }

        double SensorService::readMoisture()
        {
            if (!sensor->isConnected()) return -1.0;
            return sensor->readMoisture();
        }

        double SensorService::readPH()
        {
            if (!sensor->isConnected()) return -1.0;
            return sensor->readPH();
        }

        double SensorService::readTemperature()
        {
            if (!sensor->isConnected()) return -1.0;
            return sensor->readTemperature();
        }

        double SensorService::readHumidity()
        {
            if (!sensor->isConnected()) return -1.0;
            return sensor->readHumidity();
        }

        bool SensorService::isSensorConnected()
        {
            return sensor->isConnected();
        }

        void SensorService::reconnect(bool useReal, const std::string& port)
        {
            sensor = SensorFactory::createSensor(useReal, port);
        }

        std::string SensorService::getSensorInfo() const
        {
            return sensor->getSensorName();
        }
    }
}