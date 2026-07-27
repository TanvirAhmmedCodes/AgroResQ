#include "FarmRepository.h"

#include <sstream>

namespace AgroResQ
{
namespace Repositories
{

FarmRepository::FarmRepository()
{
    filePath = "database/farms.txt";
}

Entities::Farm FarmRepository::parse(const std::string& line) const
{
    std::stringstream stream(line);

    std::string id;
    std::string farmerName;
    std::string location;
    std::string landArea;
    std::string soilType;
    std::string cropName;

    std::getline(stream, id, ',');
    std::getline(stream, farmerName, ',');
    std::getline(stream, location, ',');
    std::getline(stream, landArea, ',');
    std::getline(stream, soilType, ',');
    std::getline(stream, cropName);

    return Entities::Farm(
        std::stoi(id),
        farmerName,
        location,
        std::stod(landArea),
        soilType,
        cropName
    );
}

bool FarmRepository::add(const Entities::Farm& farm)
{
    return fileManager.appendFile(
        filePath,
        farm.toString() + "\n");
}

std::vector<Entities::Farm> FarmRepository::getAll()
{
    std::vector<Entities::Farm> farms;

    std::vector<std::string> lines =
        fileManager.readLines(filePath);

    for (const auto& line : lines)
    {
        farms.push_back(parse(line));
    }

    return farms;
}

bool FarmRepository::getById(
    int id,
    Entities::Farm& farm)
{
    std::vector<Entities::Farm> farms = getAll();

    for (const auto& item : farms)
    {
        if (item.getId() == id)
        {
            farm = item;
            return true;
        }
    }

    return false;
}

bool FarmRepository::update(const Entities::Farm& farm)
{
    std::vector<Entities::Farm> farms = getAll();

    bool found = false;
    std::string data;

    for (auto& item : farms)
    {
        if (item.getId() == farm.getId())
        {
            item = farm;
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

bool FarmRepository::remove(int id)
{
    std::vector<Entities::Farm> farms = getAll();

    bool found = false;
    std::string data;

    for (const auto& item : farms)
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