#include "ReliefRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    ReliefRepository::ReliefRepository()
    {
        filePath = "database/relief.txt";
    }

    Entities::ReliefResource ReliefRepository::parse(const std::string& line) const
    {
        Security::XORCipher cipher;
        std::string decrypted = cipher.decrypt(line);
        std::string dataToParse = decrypted.empty() ? line : decrypted;

        std::stringstream ss(dataToParse);
        std::string id, name, category, quantity, unit, tenantId;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, category, ',');
        std::getline(ss, quantity, ',');
        std::getline(ss, unit, ',');
        std::getline(ss, tenantId);

        return Entities::ReliefResource(
            Core::safeStoi(id),
            name, category,
            Core::safeStoi(quantity),
            unit,
            tenantId
        );
    }

    bool ReliefRepository::add(const Entities::ReliefResource& resource)
    {
        Security::XORCipher cipher;
        std::string encrypted = cipher.encrypt(resource.toString());
        bool ok = fileManager.appendFile(filePath, encrypted + "\n");

        if (ok)
        {
            // Add to ledger: victimName = resource name, resourceType = category, quantity = quantity
            ledger.addEntry(resource.getName(), resource.getCategory(), resource.getQuantity());
        }
        return ok;
    }

    std::vector<Entities::ReliefResource> ReliefRepository::getAll()
    {
        std::vector<Entities::ReliefResource> resources;
        std::vector<std::string> lines = fileManager.readLines(filePath);
        for (const auto& line : lines)
        {
            if (!line.empty())
                resources.push_back(parse(line));
        }
        return resources;
    }

    bool ReliefRepository::getById(int id, Entities::ReliefResource& resource)
    {
        auto all = getAll();
        for (const auto& r : all)
        {
            if (r.getId() == id)
            {
                resource = r;
                return true;
            }
        }
        return false;
    }

    bool ReliefRepository::update(const Entities::ReliefResource& resource)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (auto& r : all)
        {
            if (r.getId() == resource.getId())
            {
                r = resource;
                found = true;
            }
            data += cipher.encrypt(r.toString()) + "\n";
        }

        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    bool ReliefRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (const auto& r : all)
        {
            if (r.getId() == id)
            {
                found = true;
                continue;
            }
            data += cipher.encrypt(r.toString()) + "\n";
        }

        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    std::vector<Entities::ReliefResource> ReliefRepository::getByTenant(const std::string& tenantId)
    {
        std::vector<Entities::ReliefResource> result;
        auto all = getAll();
        for (const auto& r : all)
        {
            if (r.getTenantId() == tenantId || tenantId == "ALL")
                result.push_back(r);
        }
        return result;
    }

    
    Ledger::ReliefLedger& ReliefRepository::getLedger()
    {
        return ledger;
    }

    bool ReliefRepository::verifyLedger()
    {
        return ledger.verifyAllEntries();
    }

    void ReliefRepository::displayLedger()
    {
        ledger.displayLedger();
    }
}
}