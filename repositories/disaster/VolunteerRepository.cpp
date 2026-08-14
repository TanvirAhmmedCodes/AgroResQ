#include "VolunteerRepository.h"
#include "../../core/StringHelper.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    VolunteerRepository::VolunteerRepository()
    {
        filePath = "database/volunteers.txt";
    }

    Entities::Volunteer VolunteerRepository::parse(const std::string& line) const
    {
        std::stringstream ss(line);
        std::string id, name, skill, location, contact, available, tenantId;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, skill, ',');
        std::getline(ss, location, ',');
        std::getline(ss, contact, ',');
        std::getline(ss, available, ',');
        std::getline(ss, tenantId);
        return Entities::Volunteer(
            Core::safeStoi(id),
            name, skill, location, contact,
            Core::safeStob(available),
            tenantId
        );
    }

    bool VolunteerRepository::add(const Entities::Volunteer& volunteer)
    {
        return fileManager.appendFile(filePath, volunteer.toString() + "\n");
    }

    std::vector<Entities::Volunteer> VolunteerRepository::getAll()
    {
        std::vector<Entities::Volunteer> volunteers;
        std::vector<std::string> lines = fileManager.readLines(filePath);
        for (const auto& line : lines)
        {
            if (!line.empty())
                volunteers.push_back(parse(line));
        }
        return volunteers;
    }

    bool VolunteerRepository::getById(int id, Entities::Volunteer& volunteer)
    {
        auto all = getAll();
        for (const auto& v : all)
        {
            if (v.getId() == id)
            {
                volunteer = v;
                return true;
            }
        }
        return false;
    }

    bool VolunteerRepository::update(const Entities::Volunteer& volunteer)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (auto& v : all)
        {
            if (v.getId() == volunteer.getId())
            {
                v = volunteer;
                found = true;
            }
            data += v.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    bool VolunteerRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (const auto& v : all)
        {
            if (v.getId() == id)
            {
                found = true;
                continue;
            }
            data += v.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    std::vector<Entities::Volunteer> VolunteerRepository::getByTenant(const std::string& tenantId)
    {
        std::vector<Entities::Volunteer> result;
        auto all = getAll();
        for (const auto& v : all)
        {
            if (v.getTenantId() == tenantId || tenantId == "ALL")
                result.push_back(v);
        }
        return result;
    }

    std::vector<Entities::Volunteer> VolunteerRepository::getAvailableVolunteers()
    {
        std::vector<Entities::Volunteer> result;
        auto all = getAll();
        for (const auto& v : all)
        {
            if (v.isAvailable())
                result.push_back(v);
        }
        return result;
    }
}
}