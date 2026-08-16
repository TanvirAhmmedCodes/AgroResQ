#include "WeatherRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    WeatherRepository::WeatherRepository()
    {
        filePath = "database/weather.txt";
        rebuildCache();
    }

    void WeatherRepository::rebuildCache()
    {
        weatherCache.clear();
        auto weathers = getAll();
        for (const auto& w : weathers)
        {
            weatherCache.add(w.getId(), w);
        }
    }

    Entities::Weather WeatherRepository::parse(const std::string& line) const
    {
        Security::XORCipher cipher;
        std::string decrypted = cipher.decrypt(line);
        std::string dataToParse = decrypted.empty() ? line : decrypted;

        std::stringstream ss(dataToParse);
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
        Security::XORCipher cipher;
        std::string encrypted = cipher.encrypt(weather.toString());
        bool ok = fileManager.appendFile(filePath, encrypted + "\n");
        if (ok)
        {
            weatherCache.add(weather.getId(), weather);
        }
        return ok;
    }

    bool WeatherRepository::update(const Entities::Weather& weather)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (auto& w : all)
        {
            if (w.getId() == weather.getId())
            {
                w = weather;
                found = true;
            }
            data += cipher.encrypt(w.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            weatherCache.add(weather.getId(), weather);
        }
        return ok;
    }

    bool WeatherRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (const auto& w : all)
        {
            if (w.getId() == id)
            {
                found = true;
                continue;
            }
            data += cipher.encrypt(w.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            weatherCache.remove(id);
        }
        return ok;
    }

    bool WeatherRepository::getById(int id, Entities::Weather& weather)
    {
        if (weatherCache.get(id, weather))
            return true;

        auto all = getAll();
        for (const auto& w : all)
        {
            if (w.getId() == id)
            {
                weather = w;
                weatherCache.add(id, w);
                return true;
            }
        }
        return false;
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