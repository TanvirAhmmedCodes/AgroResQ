#include "SensorSyncService.h"
#include "../core/AuthManager.h"
#include <iostream>

namespace AgroResQ
{
namespace Services
{

SensorSyncService::SensorSyncService() : sensorService(true, "COM3")
{
    defaultFarmId = "SENSOR_FARM";
    defaultSoilType = "Loamy";
}

void SensorSyncService::setDefaultFarmId(const std::string& farmId)
{
    defaultFarmId = farmId;
}

void SensorSyncService::setDefaultSoilType(const std::string& soilType)
{
    defaultSoilType = soilType;
}

bool SensorSyncService::syncOnce()
{
    if (!sensorService.isSensorConnected())
    {
        std::cout << "[SensorSync] Hardware not connected. Reconnecting...\n";
        sensorService.reconnect(true, "COM3");
        if (!sensorService.isSensorConnected())
        {
            std::cout << "[SensorSync] Failed to connect. Switching to simulated.\n";
            sensorService.reconnect(false);
        }
    }

    auto data = sensorService.readAllData();
    if (!data.valid)
    {
        std::cout << "[SensorSync] Failed to read sensor data.\n";
        return false;
    }

    std::cout << "[SensorSync] Read: Moisture=" << data.moisture
              << " pH=" << data.ph
              << " Temp=" << data.temperature
              << " Hum=" << data.humidity << "\n";

    // Get current tenant ID from logged-in user
    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    bool soilOk = soilService.addSoil(defaultFarmId, data.ph, data.moisture, defaultSoilType);
    bool weatherOk = weatherService.addWeather(defaultFarmId, data.temperature, data.humidity, 0.0);

    if (soilOk && weatherOk)
    {
        std::cout << "[SensorSync] Data saved successfully.\n";
        return true;
    }

    std::cout << "[SensorSync] Failed to save data.\n";
    return false;
}

bool SensorSyncService::isHardwareConnected()
{
    return sensorService.isSensorConnected();
}

std::string SensorSyncService::getSensorInfo() const
{
    return sensorService.getSensorInfo();
}

} 
}