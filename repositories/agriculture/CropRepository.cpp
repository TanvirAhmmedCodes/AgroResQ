#include "CropRepository.h"
#include "../../core/StringHelper.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    CropRepository::CropRepository()
    {
        filePath = "database/crops.txt";
    }

    Entities::Crop CropRepository::parse(const std::string& line) const
    {
        std::stringstream ss(line);
        std::string id, cropName, season, suitableSoil, waterReq, tenantId;
        std::getline(ss, id, ',');
        std::getline(ss, cropName, ',');
        std::getline(ss, season, ',');
        std::getline(ss, suitableSoil, ',');
        std::getline(ss, waterReq, ',');
        std::getline(ss, tenantId);
        return Entities::Crop(
            Core::safeStoi(id),
            cropName, season, suitableSoil,
            Core::safeStod(waterReq),
            tenantId
        );
    }

    bool CropRepository::add(const Entities::Crop& crop)
    {
        return fileManager.appendFile(filePath, crop.toString() + "\n");
    }

    std::vector<Entities::Crop> CropRepository::getAll()
    {
        std::vector<Entities::Crop> crops;
        std::vector<std::string> lines = fileManager.readLines(filePath);
        for (const auto& line : lines)
        {
            if (!line.empty())
                crops.push_back(parse(line));
        }
        return crops;
    }

    bool CropRepository::getById(int id, Entities::Crop& crop)
    {
        auto all = getAll();
        for (const auto& c : all)
        {
            if (c.getId() == id)
            {
                crop = c;
                return true;
            }
        }
        return false;
    }

    bool CropRepository::update(const Entities::Crop& crop)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (auto& c : all)
        {
            if (c.getId() == crop.getId())
            {
                c = crop;
                found = true;
            }
            data += c.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    bool CropRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (const auto& c : all)
        {
            if (c.getId() == id)
            {
                found = true;
                continue;
            }
            data += c.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    std::vector<Entities::Crop> CropRepository::getByTenant(const std::string& tenantId)
    {
        std::vector<Entities::Crop> result;
        auto all = getAll();
        for (const auto& c : all)
        {
            if (c.getTenantId() == tenantId || tenantId == "ALL")
                result.push_back(c);
        }
        return result;
    }
}
}