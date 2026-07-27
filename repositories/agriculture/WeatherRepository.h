#pragma once

#include <string>
#include <vector>

#include "../../core/FileManager.h"
#include "../../entities/Weather.h"

namespace AgroResQ
{
namespace Repositories
{

class WeatherRepository
{
private:
    Core::FileManager fileManager;
    std::string filePath;

    Entities::Weather parse(const std::string& line) const;

public:
    WeatherRepository();

    bool add(const Entities::Weather& weather);

    bool update(const Entities::Weather& weather);

    bool remove(int id);

    bool getById(
        int id,
        Entities::Weather& weather);

    std::vector<Entities::Weather> getAll();
};

}
}