#include "CropRepository.h"

#include <sstream>

namespace AgroResQ
{
namespace Repositories
{

CropRepository::CropRepository()
{
    filePath = "database/crops.txt";
}

Entities::Crop CropRepository::parse(
    const std::string& line) const
{
    std::stringstream stream(line);

    std::string id;
    std::string cropName;
    std::string season;
    std::string suitableSoil;
    std::string waterRequirement;

    std::getline(stream, id, ',');
    std::getline(stream, cropName, ',');
    std::getline(stream, season, ',');
    std::getline(stream, suitableSoil, ',');
    std::getline(stream, waterRequirement);

    return Entities::Crop(
        std::stoi(id),
        cropName,
        season,
        suitableSoil,
        std::stod(waterRequirement));
}

bool CropRepository::add(
    const Entities::Crop& crop)
{
    return fileManager.appendFile(
        filePath,
        crop.toString() + "\n");
}

std::vector<Entities::Crop> CropRepository::getAll()
{
    std::vector<Entities::Crop> crops;

    std::vector<std::string> lines =
        fileManager.readLines(filePath);

    for (const auto& line : lines)
    {
        crops.push_back(parse(line));
    }

    return crops;
}

bool CropRepository::getById(
    int id,
    Entities::Crop& crop)
{
    std::vector<Entities::Crop> crops =
        getAll();

    for (const auto& item : crops)
    {
        if (item.getId() == id)
        {
            crop = item;
            return true;
        }
    }

    return false;
}

bool CropRepository::update(
    const Entities::Crop& crop)
{
    std::vector<Entities::Crop> crops =
        getAll();

    bool found = false;

    std::string data;

    for (auto& item : crops)
    {
        if (item.getId() == crop.getId())
        {
            item = crop;
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

bool CropRepository::remove(int id)
{
    std::vector<Entities::Crop> crops =
        getAll();

    bool found = false;

    std::string data;

    for (const auto& item : crops)
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