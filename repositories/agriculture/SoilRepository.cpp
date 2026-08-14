#include "SoilRepository.h"
#include "../../core/StringHelper.h"
#include <sstream>

namespace AgroResQ
{
    namespace Repositories
    {
        SoilRepository::SoilRepository()
        {
            filePath = "database/soil.txt";
        }

        Entities::Soil SoilRepository::parse(const std::string& line) const
        {
            std::stringstream stream(line);
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
            return fileManager.appendFile(filePath, soil.toString() + "\n");
        }

        bool SoilRepository::update(const Entities::Soil& soil)
        {
            std::vector<Entities::Soil> soils = getAll();
            bool found = false;
            std::string data;
            for (auto& item : soils)
            {
                if (item.getId() == soil.getId())
                {
                    item = soil;
                    found = true;
                }
                data += item.toString() + "\n";
            }
            if (!found) return false;
            return fileManager.writeFile(filePath, data);
        }

        bool SoilRepository::remove(int id)
        {
            std::vector<Entities::Soil> soils = getAll();
            bool found = false;
            std::string data;
            for (const auto& item : soils)
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

        bool SoilRepository::getById(int id, Entities::Soil& soil)
        {
            std::vector<Entities::Soil> soils = getAll();
            for (const auto& item : soils)
            {
                if (item.getId() == id)
                {
                    soil = item;
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