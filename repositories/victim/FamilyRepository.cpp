#include "FamilyRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <sstream>

namespace AgroResQ
{
    namespace Repositories
    {
        FamilyRepository::FamilyRepository()
        {
            filePath = "database/families.txt";
            rebuildCache();
        }

        void FamilyRepository::rebuildCache()
        {
            familyCache.clear();
            auto families = getAll();
            for (const auto& f : families)
            {
                familyCache.add(f.getId(), f);
            }
        }

        std::string FamilyRepository::serialize(const Entities::Family& family)
        {
            return family.toString();
        }

        Entities::Family FamilyRepository::parse(const std::string& line)
        {
            Security::XORCipher cipher;
            std::string decrypted = cipher.decrypt(line);
            std::string dataToParse = decrypted.empty() ? line : decrypted;

            std::stringstream stream(dataToParse);
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
            Security::XORCipher cipher;
            std::string encrypted = cipher.encrypt(serialize(family));
            bool ok = fileManager.appendFile(filePath, encrypted + "\n");
            if (ok)
            {
                familyCache.add(family.getId(), family);
            }
            return ok;
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
            if (familyCache.get(id, family))
                return true;

            auto families = getAll();
            for (auto& item : families)
            {
                if (item.getId() == id)
                {
                    family = item;
                    familyCache.add(id, item);
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
            Security::XORCipher cipher;

            for (auto& item : families)
            {
                if (item.getId() == family.getId())
                {
                    item = family;
                    updated = true;
                }
                data += cipher.encrypt(serialize(item)) + "\n";
            }

            if (!updated) return false;
            bool ok = fileManager.writeFile(filePath, data);
            if (ok)
            {
                familyCache.add(family.getId(), family);
            }
            return ok;
        }

        bool FamilyRepository::remove(int id)
        {
            auto families = getAll();
            bool removed = false;
            std::string data;
            Security::XORCipher cipher;

            for (const auto& item : families)
            {
                if (item.getId() == id)
                {
                    removed = true;
                    continue;
                }
                data += cipher.encrypt(serialize(item)) + "\n";
            }

            if (!removed) return false;
            bool ok = fileManager.writeFile(filePath, data);
            if (ok)
            {
                familyCache.remove(id);
            }
            return ok;
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