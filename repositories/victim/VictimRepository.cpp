#include "VictimRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <fstream>
#include <sstream>

namespace AgroResQ
{
    namespace Repositories
    {
        VictimRepository::VictimRepository()
        {
            filePath = "database/victims.txt";
            rebuildCache();
        }

        void VictimRepository::rebuildCache()
        {
            victimCache.clear();
            auto victims = getAll();
            for (const auto& v : victims)
            {
                victimCache.add(v.getId(), v);
            }
        }

        std::string VictimRepository::serialize(const Entities::Victim& victim)
        {
            return victim.toString();
        }

        Entities::Victim VictimRepository::parse(const std::string& line)
        {
            Security::XORCipher cipher;
            std::string decrypted = cipher.decrypt(line);
            std::string dataToParse = decrypted.empty() ? line : decrypted;

            std::stringstream stream(dataToParse);
            std::string id, name, age, gender, address, vulnerable, familyId,
                        healthStatus, disabled, rescued, reliefReceived, missing,
                        priorityScore, shelterId, tenantId;

            std::getline(stream, id, ',');
            std::getline(stream, name, ',');
            std::getline(stream, age, ',');
            std::getline(stream, gender, ',');
            std::getline(stream, address, ',');
            std::getline(stream, vulnerable, ',');
            std::getline(stream, familyId, ',');
            std::getline(stream, healthStatus, ',');
            std::getline(stream, disabled, ',');
            std::getline(stream, rescued, ',');
            std::getline(stream, reliefReceived, ',');
            std::getline(stream, missing, ',');
            std::getline(stream, priorityScore, ',');
            std::getline(stream, shelterId, ',');
            std::getline(stream, tenantId);

            return Entities::Victim(
                Core::safeStoi(id),
                name,
                Core::safeStoi(age),
                gender,
                address,
                Core::safeStob(vulnerable),
                Core::safeStoi(familyId),
                healthStatus,
                Core::safeStob(disabled),
                Core::safeStob(rescued),
                Core::safeStob(reliefReceived),
                Core::safeStob(missing),
                Core::safeStoi(priorityScore),
                Core::safeStoi(shelterId),
                tenantId
            );
        }

        bool VictimRepository::add(const Entities::Victim& victim)
        {
            Security::XORCipher cipher;
            std::string encrypted = cipher.encrypt(serialize(victim));
            bool ok = fileManager.appendFile(filePath, encrypted + "\n");
            if (ok)
            {
                victimCache.add(victim.getId(), victim);
            }
            return ok;
        }

        std::vector<Entities::Victim> VictimRepository::getAll()
        {
            std::vector<Entities::Victim> victims;
            std::vector<std::string> lines = fileManager.readLines(filePath);
            for (const auto& line : lines)
            {
                if (!line.empty())
                    victims.push_back(parse(line));
            }
            return victims;
        }

        bool VictimRepository::getById(int id, Entities::Victim& victim)
        {
            if (victimCache.get(id, victim))
                return true;

            auto victims = getAll();
            for (auto& item : victims)
            {
                if (item.getId() == id)
                {
                    victim = item;
                    victimCache.add(id, item);
                    return true;
                }
            }
            return false;
        }

        bool VictimRepository::update(const Entities::Victim& victim)
        {
            auto victims = getAll();
            bool updated = false;
            std::string data;
            Security::XORCipher cipher;

            for (auto& item : victims)
            {
                if (item.getId() == victim.getId())
                {
                    item = victim;
                    updated = true;
                }
                data += cipher.encrypt(serialize(item)) + "\n";
            }

            if (!updated) return false;
            bool ok = fileManager.writeFile(filePath, data);
            if (ok)
            {
                victimCache.add(victim.getId(), victim);
            }
            return ok;
        }

        bool VictimRepository::remove(int id)
        {
            auto victims = getAll();
            bool removed = false;
            std::string data;
            Security::XORCipher cipher;

            for (const auto& item : victims)
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
                victimCache.remove(id);
            }
            return ok;
        }

        std::vector<Entities::Victim> VictimRepository::getByTenant(const std::string& tenantId)
        {
            std::vector<Entities::Victim> result;
            auto all = getAll();
            for (const auto& v : all)
            {
                if (v.getTenantId() == tenantId || tenantId == "ALL")
                    result.push_back(v);
            }
            return result;
        }
    }
}