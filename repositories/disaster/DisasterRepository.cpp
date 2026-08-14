#include "DisasterRepository.h"
#include "../../core/StringHelper.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    DisasterRepository::DisasterRepository()
    {
        filePath = "database/disaster.txt";
    }

    Entities::Disaster DisasterRepository::parse(const std::string& line) const
    {
        std::stringstream stream(line);
        std::string id, name, type, location, date, severity, division, district,
                    disasterType, affectedPeople, status, tenantId;
        std::getline(stream, id, ',');
        std::getline(stream, name, ',');
        std::getline(stream, type, ',');
        std::getline(stream, location, ',');
        std::getline(stream, date, ',');
        std::getline(stream, severity, ',');
        std::getline(stream, division, ',');
        std::getline(stream, district, ',');
        std::getline(stream, disasterType, ',');
        std::getline(stream, affectedPeople, ',');
        std::getline(stream, status, ',');
        std::getline(stream, tenantId);
        return Entities::Disaster(
            Core::safeStoi(id),
            name,
            type,
            location,
            date,
            Core::safeStoi(severity, 1),
            Core::safeStoi(division),
            Core::safeStoi(district),
            Core::safeStoi(disasterType),
            Core::safeStoi(affectedPeople),
            Core::safeStoi(status, 1),
            tenantId
        );
    }

    bool DisasterRepository::add(const Entities::Disaster& disaster)
    {
        return fileManager.appendFile(filePath, disaster.toString() + "\n");
    }

    bool DisasterRepository::update(const Entities::Disaster& disaster)
    {
        std::vector<Entities::Disaster> disasters = getAll();
        bool found = false;
        std::string data;
        for (auto& item : disasters)
        {
            if (item.getId() == disaster.getId())
            {
                item = disaster;
                found = true;
            }
            data += item.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    bool DisasterRepository::remove(int id)
    {
        std::vector<Entities::Disaster> disasters = getAll();
        bool found = false;
        std::string data;
        for (const auto& item : disasters)
        {
            if (item.getId() == id)
            {
                found = true;
                continue;
            }
            data += item.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    bool DisasterRepository::getById(int id, Entities::Disaster& disaster)
    {
        std::vector<Entities::Disaster> disasters = getAll();
        for (const auto& item : disasters)
        {
            if (item.getId() == id)
            {
                disaster = item;
                return true;
            }
        }
        return false;
    }

    std::vector<Entities::Disaster> DisasterRepository::getAll()
    {
        std::vector<Entities::Disaster> disasters;
        std::vector<std::string> lines = fileManager.readLines(filePath);
        for (const auto& line : lines)
        {
            if (!line.empty())
                disasters.push_back(parse(line));
        }
        return disasters;
    }

    std::vector<Entities::Disaster> DisasterRepository::getByTenant(const std::string& tenantId)
    {
        std::vector<Entities::Disaster> result;
        auto all = getAll();
        for (const auto& d : all)
        {
            if (d.getTenantId() == tenantId || tenantId == "ALL")
                result.push_back(d);
        }
        return result;
    }
}
}