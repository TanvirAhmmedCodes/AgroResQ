#include "WeatherRepository.h"
#include "../../core/StringHelper.h"
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
        std::stringstream ss(line);
        std::string id, location, temperature, humidity, rainfall, tenantId;
        std::getline(ss, id, ',');
        std::getline(ss, location, ',');
        std::getline(ss, temperature, ',');
        std::getline(ss, humidity, ',');
        std::getline(ss, rainfall, ',');
        std::getline(ss, tenantId);
        return Entities::Weather(
            Core::safeStoi(id),
            location,
            Core::safeStod(temperature),
            Core::safeStod(humidity),
            Core::safeStod(rainfall),
            tenantId
        );
    }

    bool WeatherRepository::add(const Entities::Weather& weather)
    {
        return fileManager.appendFile(filePath, weather.toString() + "\n");
    }

    std::vector<Entities::Weather> WeatherRepository::getAll()
    {
        std::vector<Entities::Weather> weathers;
        std::vector<std::string> lines = fileManager.readLines(filePath);
        for (const auto& line : lines)
        {
            if (!line.empty())
                weathers.push_back(parse(line));
        }
        return weathers;
    }

    bool WeatherRepository::getById(int id, Entities::Weather& weather)
    {
        auto all = getAll();
        for (const auto& w : all)
        {
            if (w.getId() == id)
            {
                weather = w;
                return true;
            }
        }
        return false;
    }

    bool WeatherRepository::update(const Entities::Weather& weather)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (auto& w : all)
        {
            if (w.getId() == weather.getId())
            {
                w = weather;
                found = true;
            }
            data += w.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    bool WeatherRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (const auto& w : all)
        {
            if (w.getId() == id)
            {
                found = true;
                continue;
            }
            data += w.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    std::vector<Entities::Weather> WeatherRepository::getByTenant(const std::string& tenantId)
    {
        std::vector<Entities::Weather> result;
        auto all = getAll();
        for (const auto& w : all)
        {
            if (w.getTenantId() == tenantId || tenantId == "ALL")
                result.push_back(w);
        }
        return result;
    }
}
}