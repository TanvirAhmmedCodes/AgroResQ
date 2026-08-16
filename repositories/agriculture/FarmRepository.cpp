#include "FarmRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    FarmRepository::FarmRepository()
    {
        filePath = "database/farms.txt";
        rebuildCache();
    }

    void FarmRepository::rebuildCache()
    {
        farmCache.clear();
        auto farms = getAll();
        for (const auto& f : farms)
        {
            farmCache.add(f.getId(), f);
        }
    }

    Entities::Farm FarmRepository::parse(const std::string& line) const
    {
        Security::XORCipher cipher;
        std::string decrypted = cipher.decrypt(line);
        std::string dataToParse = decrypted.empty() ? line : decrypted;

        std::stringstream ss(dataToParse);
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
        Security::XORCipher cipher;
        std::string encrypted = cipher.encrypt(farm.toString());
        bool ok = fileManager.appendFile(filePath, encrypted + "\n");
        if (ok)
        {
            farmCache.add(farm.getId(), farm);
        }
        return ok;
    }

    bool FarmRepository::update(const Entities::Farm& farm)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (auto& f : all)
        {
            if (f.getId() == farm.getId())
            {
                f = farm;
                found = true;
            }
            data += cipher.encrypt(f.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            farmCache.add(farm.getId(), farm);
        }
        return ok;
    }

    bool FarmRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (const auto& f : all)
        {
            if (f.getId() == id)
            {
                found = true;
                continue;
            }
            data += cipher.encrypt(f.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            farmCache.remove(id);
        }
        return ok;
    }

    bool FarmRepository::getById(int id, Entities::Farm& farm)
    {
        if (farmCache.get(id, farm))
            return true;

        auto all = getAll();
        for (const auto& f : all)
        {
            if (f.getId() == id)
            {
                farm = f;
                farmCache.add(id, f);
                return true;
            }
        }
        return false;
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