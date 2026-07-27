#include "WeatherRepository.h"

#include <sstream>

namespace AgroResQ
{
namespace Repositories
{

WeatherRepository::WeatherRepository()
{
    filePath = "database/weather.txt";
}

Entities::Weather WeatherRepository::parse(const std::string& line) const
{
    std::stringstream stream(line);

    std::string id;
    std::string location;
    std::string temperature;
    std::string humidity;
    std::string rainfall;

    std::getline(stream, id, ',');
    std::getline(stream, location, ',');
    std::getline(stream, temperature, ',');
    std::getline(stream, humidity, ',');
    std::getline(stream, rainfall);

    return Entities::Weather(
        std::stoi(id),
        location,
        std::stod(temperature),
        std::stod(humidity),
        std::stod(rainfall));
}

bool WeatherRepository::add(const Entities::Weather& weather)
{
    return fileManager.appendFile(
        filePath,
        weather.toString() + "\n");
}

std::vector<Entities::Weather> WeatherRepository::getAll()
{
    std::vector<Entities::Weather> weathers;

    std::vector<std::string> lines =
        fileManager.readLines(filePath);

    for (const auto& line : lines)
    {
        weathers.push_back(parse(line));
    }

    return weathers;
}

bool WeatherRepository::getById(
    int id,
    Entities::Weather& weather)
{
    std::vector<Entities::Weather> weathers =
        getAll();

    for (const auto& item : weathers)
    {
        if (item.getId() == id)
        {
            weather = item;
            return true;
        }
    }

    return false;
}

bool WeatherRepository::update(
    const Entities::Weather& weather)
{
    std::vector<Entities::Weather> weathers =
        getAll();

    bool found = false;

    std::string data;

    for (auto& item : weathers)
    {
        if (item.getId() == weather.getId())
        {
            item = weather;
            found = true;
        }

        data += item.toString() + "\n";
    }

    if (!found)
    {
        return false;
    }

    return fileManager.writeFile(filePath, data);
}

bool WeatherRepository::remove(int id)
{
    std::vector<Entities::Weather> weathers =
        getAll();

    bool found = false;

    std::string data;

    for (const auto& item : weathers)
    {
        if (item.getId() == id)
        {
            found = true;
            continue;
        }

        data += item.toString() + "\n";
    }

    if (!found)
    {
        return false;
    }

    return fileManager.writeFile(filePath, data);
}

}
}