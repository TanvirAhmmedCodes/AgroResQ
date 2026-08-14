#include "FamilyRepository.h"
#include "../../core/StringHelper.h"
#include <sstream>

namespace AgroResQ
{
    namespace Repositories
    {
        FamilyRepository::FamilyRepository()
        {
            filePath = "database/families.txt";
        }

        std::string FamilyRepository::serialize(const Entities::Family& family)
        {
            return family.toString();
        }

        Entities::Family FamilyRepository::parse(const std::string& line)
        {
            std::stringstream stream(line);
            std::string id, headName, address, contact, memberCount, displaced, tenantId;
            std::getline(stream, id, ',');
            std::getline(stream, headName, ',');
            std::getline(stream, address, ',');
            std::getline(stream, contact, ',');
            std::getline(stream, memberCount, ',');
            std::getline(stream, displaced, ',');
            std::getline(stream, tenantId);
            return Entities::Family(
                Core::safeStoi(id),
                headName,
                address,
                contact,
                Core::safeStoi(memberCount),
                Core::safeStob(displaced),
                tenantId
            );
        }

        bool FamilyRepository::add(const Entities::Family& family)
        {
            return fileManager.appendFile(filePath, serialize(family) + "\n");
        }

        std::vector<Entities::Family> FamilyRepository::getAll()
        {
            std::vector<Entities::Family> families;
            std::vector<std::string> lines = fileManager.readLines(filePath);
            for (const auto& line : lines)
            {
                if (!line.empty())
                    families.push_back(parse(line));
            }
            return families;
        }

        bool FamilyRepository::getById(int id, Entities::Family& family)
        {
            auto families = getAll();
            for (auto& item : families)
            {
                if (item.getId() == id)
                {
                    family = item;
                    return true;
                }
            }
            return false;
        }

        bool FamilyRepository::update(const Entities::Family& family)
        {
            auto families = getAll();
            bool updated = false;
            std::string data;
            for (auto& item : families)
            {
                if (item.getId() == family.getId())
                {
                    item = family;
                    updated = true;
                }
                data += serialize(item) + "\n";
            }
            if (!updated) return false;
            return fileManager.writeFile(filePath, data);
        }

        bool FamilyRepository::remove(int id)
        {
            auto families = getAll();
            bool removed = false;
            std::string data;
            for (auto& item : families)
            {
                if (item.getId() == id)
                {
                    removed = true;
                    continue;
                }
                data += serialize(item) + "\n";
            }
            if (!removed) return false;
            return fileManager.writeFile(filePath, data);
        }

        std::vector<Entities::Family> FamilyRepository::getDisplacedFamilies()
        {
            std::vector<Entities::Family> displaced;
            auto all = getAll();
            for (auto& f : all)
            {
                if (f.isDisplaced())
                    displaced.push_back(f);
            }
            return displaced;
        }

        std::vector<Entities::Family> FamilyRepository::getByTenant(const std::string& tenantId)
        {
            std::vector<Entities::Family> result;
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