#include "SoilRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <sstream>

namespace AgroResQ
{
    namespace Repositories
    {
        SoilRepository::SoilRepository()
        {
            filePath = "database/soil.txt";
            rebuildCache();
        }

        void SoilRepository::rebuildCache()
        {
            soilCache.clear();
            auto soils = getAll();
            for (const auto& s : soils)
            {
                soilCache.add(s.getId(), s);
            }
        }

        Entities::Soil SoilRepository::parse(const std::string& line) const
        {
            Security::XORCipher cipher;
            std::string decrypted = cipher.decrypt(line);
            std::string dataToParse = decrypted.empty() ? line : decrypted;

            std::stringstream stream(dataToParse);
            std::string id, farmId, phLevel, moisture, soilType, tenantId;
            std::getline(stream, id, ',');
            std::getline(stream, farmId, ',');
            std::getline(stream, phLevel, ',');
            std::getline(stream, moisture, ',');
            std::getline(stream, soilType, ',');
            std::getline(stream, tenantId);

            return Entities::Soil(
                Core::safeStoi(id),
                farmId,
                Core::safeStod(phLevel),
                Core::safeStod(moisture),
                soilType,
                tenantId
            );
        }

        bool SoilRepository::add(const Entities::Soil& soil)
        {
            Security::XORCipher cipher;
            std::string encrypted = cipher.encrypt(soil.toString());
            bool ok = fileManager.appendFile(filePath, encrypted + "\n");
            if (ok)
            {
                soilCache.add(soil.getId(), soil);
            }
            return ok;
        }

        bool SoilRepository::update(const Entities::Soil& soil)
        {
            std::vector<Entities::Soil> soils = getAll();
            bool found = false;
            std::string data;
            Security::XORCipher cipher;

            for (auto& item : soils)
            {
                if (item.getId() == soil.getId())
                {
                    item = soil;
                    found = true;
                }
                data += cipher.encrypt(item.toString()) + "\n";
            }

            if (!found) return false;
            bool ok = fileManager.writeFile(filePath, data);
            if (ok)
            {
                soilCache.add(soil.getId(), soil);
            }
            return ok;
        }

        bool SoilRepository::remove(int id)
        {
            std::vector<Entities::Soil> soils = getAll();
            bool found = false;
            std::string data;
            Security::XORCipher cipher;

            for (const auto& item : soils)
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
                soilCache.remove(id);
            }
            return ok;
        }

        bool SoilRepository::getById(int id, Entities::Soil& soil)
        {
            if (soilCache.get(id, soil))
                return true;

            std::vector<Entities::Soil> soils = getAll();
            for (const auto& item : soils)
            {
                if (item.getId() == id)
                {
                    soil = item;
                    soilCache.add(id, item);
                    return true;
                }
            }
            return false;
        }

        std::vector<Entities::Soil> SoilRepository::getAll()
        {
            std::vector<Entities::Soil> soils;
            std::vector<std::string> lines = fileManager.readLines(filePath);
            for (const auto& line : lines)
            {
                if (!line.empty())
                    soils.push_back(parse(line));
            }
            return soils;
        }

        std::vector<Entities::Soil> SoilRepository::getByTenant(const std::string& tenantId)
        {
            std::vector<Entities::Soil> result;
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