#include "FarmRepository.h"
#include "../../core/StringHelper.h"
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
        std::stringstream ss(line);
        std::string id, farmerName, location, landArea, soilType, cropName, tenantId;
        std::getline(ss, id, ',');
        std::getline(ss, farmerName, ',');
        std::getline(ss, location, ',');
        std::getline(ss, landArea, ',');
        std::getline(ss, soilType, ',');
        std::getline(ss, cropName, ',');
        std::getline(ss, tenantId);
        return Entities::Farm(
            Core::safeStoi(id),
            farmerName, location,
            Core::safeStod(landArea),
            soilType, cropName,
            tenantId
        );
    }

    bool FarmRepository::add(const Entities::Farm& farm)
    {
        return fileManager.appendFile(filePath, farm.toString() + "\n");
    }

    std::vector<Entities::Farm> FarmRepository::getAll()
    {
        std::vector<Entities::Farm> farms;
        std::vector<std::string> lines = fileManager.readLines(filePath);
        for (const auto& line : lines)
        {
            if (!line.empty())
                farms.push_back(parse(line));
        }
        return farms;
    }

    bool FarmRepository::getById(int id, Entities::Farm& farm)
    {
        auto all = getAll();
        for (const auto& f : all)
        {
            if (f.getId() == id)
            {
                farm = f;
                return true;
            }
        }
        return false;
    }

    bool FarmRepository::update(const Entities::Farm& farm)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (auto& f : all)
        {
            if (f.getId() == farm.getId())
            {
                f = farm;
                found = true;
            }
            data += f.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    bool FarmRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (const auto& f : all)
        {
            if (f.getId() == id)
            {
                found = true;
                continue;
            }
            data += f.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    std::vector<Entities::Farm> FarmRepository::getByTenant(const std::string& tenantId)
    {
        std::vector<Entities::Farm> result;
        auto all = getAll();
        for (const auto& f : all)
        {
            if (f.getTenantId() == tenantId || tenantId == "ALL")
                result.push_back(f);
        }
        return result;
    }
}
}