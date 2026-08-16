#include "ShelterRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    ShelterRepository::ShelterRepository()
    {
        filePath = "database/shelters.txt";
        rebuildCache();
    }

    void ShelterRepository::rebuildCache()
    {
        shelterCache.clear();
        auto shelters = getAll();
        for (const auto& s : shelters)
        {
            shelterCache.add(s.getId(), s);
        }
    }

    Entities::Shelter ShelterRepository::parse(const std::string& line) const
    {
        Security::XORCipher cipher;
        std::string decrypted = cipher.decrypt(line);
        std::string dataToParse = decrypted.empty() ? line : decrypted;

        std::stringstream ss(dataToParse);
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
        Security::XORCipher cipher;
        std::string encrypted = cipher.encrypt(shelter.toString());
        bool ok = fileManager.appendFile(filePath, encrypted + "\n");
        if (ok)
        {
            shelterCache.add(shelter.getId(), shelter);
        }
        return ok;
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
        if (shelterCache.get(id, shelter))
            return true;

        auto shelters = getAll();
        for (const auto& s : shelters)
        {
            if (s.getId() == id)
            {
                shelter = s;
                shelterCache.add(id, s);
                return true;
            }
        }
        return false;
    }

    bool ShelterRepository::update(const Entities::Shelter& shelter)
    {
        auto shelters = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (auto& s : shelters)
        {
            if (s.getId() == shelter.getId())
            {
                s = shelter;
                found = true;
            }
            data += cipher.encrypt(s.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            shelterCache.add(shelter.getId(), shelter);
        }
        return ok;
    }

    bool ShelterRepository::remove(int id)
    {
        auto shelters = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (const auto& s : shelters)
        {
            if (s.getId() == id)
            {
                found = true;
                continue;
            }
            data += cipher.encrypt(s.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            shelterCache.remove(id);
        }
        return ok;
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