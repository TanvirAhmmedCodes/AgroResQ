#pragma once
#include "../hardware/SensorService.h"
#include "../services/SoilService.h"
#include "../services/WeatherService.h"
#include <string>

namespace AgroResQ
{
namespace Services
{

class SensorSyncService
{
private:
    Hardware::SensorService sensorService;
    SoilService soilService;
    WeatherService weatherService;
    std::string defaultFarmId;
    std::string defaultSoilType;

public:
    SensorSyncService();

    void setDefaultFarmId(const std::string& farmId);
    void setDefaultSoilType(const std::string& soilType);

    bool syncOnce(); 

   
    bool isHardwareConnected();

    std::string getSensorInfo() const; 
};

} 
} 