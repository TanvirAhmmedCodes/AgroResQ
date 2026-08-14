#include "WeatherService.h"
#include "../core/AuthManager.h"

namespace AgroResQ
{
namespace Services
{

WeatherService::WeatherService() = default;

bool WeatherService::addWeather(
    const std::string& location,
    double temperature,
    double humidity,
    double rainfall)
{
    if (location.empty())
        return false;

    if (humidity < 0 || humidity > 100)
        return false;

    if (rainfall < 0)
        return false;

    int id = idGenerator.generateNextId("database/weather.txt");
    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::Weather weather(
        id,
        location,
        temperature,
        humidity,
        rainfall,
        tenantId);

    return weatherRepository.add(weather);
}

bool WeatherService::updateWeather(
    int id,
    const std::string& location,
    double temperature,
    double humidity,
    double rainfall)
{
    if (location.empty())
        return false;

    if (humidity < 0 || humidity > 100)
        return false;

    if (rainfall < 0)
        return false;

    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::Weather weather(
        id,
        location,
        temperature,
        humidity,
        rainfall,
        tenantId);

    return weatherRepository.update(weather);
}

bool WeatherService::deleteWeather(int id)
{
    return weatherRepository.remove(id);
}

bool WeatherService::searchWeather(
    int id,
    Entities::Weather& weather)
{
    return weatherRepository.getById(id, weather);
}

std::vector<Entities::Weather> WeatherService::getAllWeather()
{
    return weatherRepository.getAll();
}

}
}