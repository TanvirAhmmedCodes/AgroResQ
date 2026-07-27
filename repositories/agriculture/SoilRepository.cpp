#include "SoilRepository.h"

#include <sstream>

namespace AgroResQ
{
namespace Repositories
{

SoilRepository::SoilRepository()
{
    filePath = "database/soil.txt";
}

Entities::Soil SoilRepository::parse(const std::string& line) const
{
    std::stringstream stream(line);

    std::string id;
    std::string farmId;
    std::string phLevel;
    std::string moisture;
    std::string soilType;

    std::getline(stream, id, ',');
    std::getline(stream, farmId, ',');
    std::getline(stream, phLevel, ',');
    std::getline(stream, moisture, ',');
    std::getline(stream, soilType);

    return Entities::Soil(
        std::stoi(id),
        farmId,
        std::stod(phLevel),
        std::stod(moisture),
        soilType);
}

bool SoilRepository::add(const Entities::Soil& soil)
{
    return fileManager.appendFile(
        filePath,
        soil.toString() + "\n");
}

std::vector<Entities::Soil> SoilRepository::getAll()
{
    std::vector<Entities::Soil> soils;

    std::vector<std::string> lines =
        fileManager.readLines(filePath);

    for (const auto& line : lines)
    {
        soils.push_back(parse(line));
    }

    return soils;
}

bool SoilRepository::getById(
    int id,
    Entities::Soil& soil)
{
    std::vector<Entities::Soil> soils = getAll();

    for (const auto& item : soils)
    {
        if (item.getId() == id)
        {
            soil = item;
            return true;
        }
    }

    return false;
}

bool SoilRepository::update(const Entities::Soil& soil)
{
    std::vector<Entities::Soil> soils = getAll();

    bool found = false;
    std::string data;

    for (auto& item : soils)
    {
        if (item.getId() == soil.getId())
        {
            item = soil;
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

bool SoilRepository::remove(int id)
{
    std::vector<Entities::Soil> soils = getAll();

    bool found = false;
    std::string data;

    for (const auto& item : soils)
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