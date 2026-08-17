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

    // ===== Log the data with nice formatting =====
    std::cout << "\n╔════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  🌾 SENSOR DATA RECEIVED FROM ESP32                          ║\n";
    std::cout << "╠════════════════════════════════════════════════════════════════╣\n";
    std::cout << "║  Soil Moisture : " << data.moisture << "%";
    for(int i = 0; i < 22 - std::to_string(data.moisture).length(); i++) std::cout << " ";
    std::cout << "║\n";
    std::cout << "║  pH Level      : " << data.ph;
    for(int i = 0; i < 22 - std::to_string(data.ph).length(); i++) std::cout << " ";
    std::cout << "║\n";
    std::cout << "║  Temperature   : " << data.temperature << "°C";
    for(int i = 0; i < 22 - std::to_string(data.temperature).length(); i++) std::cout << " ";
    std::cout << "║\n";
    std::cout << "║  Humidity      : " << data.humidity << "%";
    for(int i = 0; i < 22 - std::to_string(data.humidity).length(); i++) std::cout << " ";
    std::cout << "║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════╝\n\n";

    // ===== Get current tenant ID =====
    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    // ===== Save to database =====
    bool soilOk = soilService.addSoil(defaultFarmId, data.ph, data.moisture, defaultSoilType);
    bool weatherOk = weatherService.addWeather(defaultFarmId, data.temperature, data.humidity, 0.0);

    if (soilOk && weatherOk)
    {
        std::cout << "[SensorSync] ✅ Data saved successfully to database.\n";
        return true;
    }

    std::cout << "[SensorSync] ❌ Failed to save data.\n";
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