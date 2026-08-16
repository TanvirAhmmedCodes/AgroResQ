#include "CropRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    CropRepository::CropRepository()
    {
        filePath = "database/crops.txt";
        rebuildCache();
    }

    void CropRepository::rebuildCache()
    {
        cropCache.clear();
        auto crops = getAll();
        for (const auto& c : crops)
        {
            cropCache.add(c.getId(), c);
        }
    }

    Entities::Crop CropRepository::parse(const std::string& line) const
    {
        Security::XORCipher cipher;
        std::string decrypted = cipher.decrypt(line);
        std::string dataToParse = decrypted.empty() ? line : decrypted;

        std::stringstream ss(dataToParse);
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
        Security::XORCipher cipher;
        std::string encrypted = cipher.encrypt(crop.toString());
        bool ok = fileManager.appendFile(filePath, encrypted + "\n");
        if (ok)
        {
            cropCache.add(crop.getId(), crop);
        }
        return ok;
    }

    bool CropRepository::update(const Entities::Crop& crop)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (auto& c : all)
        {
            if (c.getId() == crop.getId())
            {
                c = crop;
                found = true;
            }
            data += cipher.encrypt(c.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            cropCache.add(crop.getId(), crop);
        }
        return ok;
    }

    bool CropRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (const auto& c : all)
        {
            if (c.getId() == id)
            {
                found = true;
                continue;
            }
            data += cipher.encrypt(c.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            cropCache.remove(id);
        }
        return ok;
    }

    bool CropRepository::getById(int id, Entities::Crop& crop)
    {
        if (cropCache.get(id, crop))
            return true;

        auto all = getAll();
        for (const auto& c : all)
        {
            if (c.getId() == id)
            {
                crop = c;
                cropCache.add(id, c);
                return true;
            }
        }
        return false;
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