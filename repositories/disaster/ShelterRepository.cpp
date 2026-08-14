#include "ShelterRepository.h"
#include "../../core/StringHelper.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    ShelterRepository::ShelterRepository()
    {
        filePath = "database/shelters.txt";
    }

    Entities::Shelter ShelterRepository::parse(const std::string& line) const
    {
        std::stringstream ss(line);
        std::string id, name, location, capacity, occupied, tenantId;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, location, ',');
        std::getline(ss, capacity, ',');
        std::getline(ss, occupied, ',');
        std::getline(ss, tenantId);
        return Entities::Shelter(
            Core::safeStoi(id),
            name, location,
            Core::safeStoi(capacity),
            Core::safeStoi(occupied),
            tenantId
        );
    }

    bool ShelterRepository::add(const Entities::Shelter& shelter)
    {
        return fileManager.appendFile(filePath, shelter.toString() + "\n");
    }

    std::vector<Entities::Shelter> ShelterRepository::getAll()
    {
        std::vector<Entities::Shelter> shelters;
        std::vector<std::string> lines = fileManager.readLines(filePath);
        for (const auto& line : lines)
        {
            if (!line.empty())
                shelters.push_back(parse(line));
        }
        return shelters;
    }

    bool ShelterRepository::getById(int id, Entities::Shelter& shelter)
    {
        auto all = getAll();
        for (const auto& s : all)
        {
            if (s.getId() == id)
            {
                shelter = s;
                return true;
            }
        }
        return false;
    }

    bool ShelterRepository::update(const Entities::Shelter& shelter)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (auto& s : all)
        {
            if (s.getId() == shelter.getId())
            {
                s = shelter;
                found = true;
            }
            data += s.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    bool ShelterRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (const auto& s : all)
        {
            if (s.getId() == id)
            {
                found = true;
                continue;
            }
            data += s.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    std::vector<Entities::Shelter> ShelterRepository::getByTenant(const std::string& tenantId)
    {
        std::vector<Entities::Shelter> result;
        auto all = getAll();
        for (const auto& s : all)
        {
            if (s.getTenantId() == tenantId || tenantId == "ALL")
                result.push_back(s);
        }
        return result;
    }
}
}