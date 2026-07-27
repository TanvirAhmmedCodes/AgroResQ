#pragma once

#include <vector>

#include "../core/IDGenerator.h"

#include "../entities/Weather.h"

#include "../repositories/agriculture/WeatherRepository.h"

namespace AgroResQ
{
namespace Services
{

class WeatherService
{
private:
    Repositories::WeatherRepository weatherRepository;

    Core::IDGenerator idGenerator;

public:
    WeatherService();

    bool addWeather(
        const std::string& location,
        double temperature,
        double humidity,
        double rainfall);

    bool updateWeather(
        int id,
        const std::string& location,
        double temperature,
        double humidity,
        double rainfall);

    bool deleteWeather(int id);

    bool searchWeather(
        int id,
        Entities::Weather& weather);

    std::vector<Entities::Weather> getAllWeather();
};

}
}