#include "DisasterRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    DisasterRepository::DisasterRepository()
    {
        filePath = "database/disaster.txt";
        rebuildCache();
    }

    void DisasterRepository::rebuildCache()
    {
        disasterCache.clear();
        auto disasters = getAll();
        for (const auto& d : disasters)
        {
            disasterCache.add(d.getId(), d);
        }
    }

    Entities::Disaster DisasterRepository::parse(const std::string& line) const
    {
        Security::XORCipher cipher;
        std::string decrypted = cipher.decrypt(line);
        std::string dataToParse = decrypted.empty() ? line : decrypted;

        std::stringstream stream(dataToParse);
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
        Security::XORCipher cipher;
        std::string encrypted = cipher.encrypt(disaster.toString());
        bool ok = fileManager.appendFile(filePath, encrypted + "\n");
        if (ok)
        {
            disasterCache.add(disaster.getId(), disaster);
        }
        return ok;
    }

    bool DisasterRepository::update(const Entities::Disaster& disaster)
    {
        std::vector<Entities::Disaster> disasters = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (auto& item : disasters)
        {
            if (item.getId() == disaster.getId())
            {
                item = disaster;
                found = true;
            }
            data += cipher.encrypt(item.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            disasterCache.add(disaster.getId(), disaster);
        }
        return ok;
    }

    bool DisasterRepository::remove(int id)
    {
        std::vector<Entities::Disaster> disasters = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (const auto& item : disasters)
        {
            if (item.getId() == id)
            {
                found = true;
                continue;
            }
            data += cipher.encrypt(item.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            disasterCache.remove(id);
        }
        return ok;
    }

    bool DisasterRepository::getById(int id, Entities::Disaster& disaster)
    {
        if (disasterCache.get(id, disaster))
            return true;

        std::vector<Entities::Disaster> disasters = getAll();
        for (const auto& item : disasters)
        {
            if (item.getId() == id)
            {
                disaster = item;
                disasterCache.add(id, item);
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