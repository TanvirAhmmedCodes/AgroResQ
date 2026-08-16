#include "VolunteerRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    VolunteerRepository::VolunteerRepository()
    {
        filePath = "database/volunteers.txt";
        rebuildCache();
    }

    void VolunteerRepository::rebuildCache()
    {
        volunteerCache.clear();
        auto volunteers = getAll();
        for (const auto& v : volunteers)
        {
            volunteerCache.add(v.getId(), v);
        }
    }

    Entities::Volunteer VolunteerRepository::parse(const std::string& line) const
    {
        Security::XORCipher cipher;
        std::string decrypted = cipher.decrypt(line);
        std::string dataToParse = decrypted.empty() ? line : decrypted;

        std::stringstream ss(dataToParse);
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
        Security::XORCipher cipher;
        std::string encrypted = cipher.encrypt(volunteer.toString());
        bool ok = fileManager.appendFile(filePath, encrypted + "\n");
        if (ok)
        {
            volunteerCache.add(volunteer.getId(), volunteer);
        }
        return ok;
    }

    bool VolunteerRepository::update(const Entities::Volunteer& volunteer)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (auto& v : all)
        {
            if (v.getId() == volunteer.getId())
            {
                v = volunteer;
                found = true;
            }
            data += cipher.encrypt(v.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            volunteerCache.add(volunteer.getId(), volunteer);
        }
        return ok;
    }

    bool VolunteerRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (const auto& v : all)
        {
            if (v.getId() == id)
            {
                found = true;
                continue;
            }
            data += cipher.encrypt(v.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            volunteerCache.remove(id);
        }
        return ok;
    }

    bool VolunteerRepository::getById(int id, Entities::Volunteer& volunteer)
    {
        if (volunteerCache.get(id, volunteer))
            return true;

        auto all = getAll();
        for (const auto& v : all)
        {
            if (v.getId() == id)
            {
                volunteer = v;
                volunteerCache.add(id, v);
                return true;
            }
        }
        return false;
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