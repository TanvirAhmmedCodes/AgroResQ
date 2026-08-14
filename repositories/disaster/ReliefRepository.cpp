#include "ReliefRepository.h"
#include "../../core/StringHelper.h"
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
        std::stringstream ss(line);
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
        return fileManager.appendFile(filePath, resource.toString() + "\n");
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
        for (auto& r : all)
        {
            if (r.getId() == resource.getId())
            {
                r = resource;
                found = true;
            }
            data += r.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    bool ReliefRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (const auto& r : all)
        {
            if (r.getId() == id)
            {
                found = true;
                continue;
            }
            data += r.toString() + "\n";
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
}
}