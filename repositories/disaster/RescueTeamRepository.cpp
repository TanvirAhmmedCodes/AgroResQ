#include "RescueTeamRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    RescueTeamRepository::RescueTeamRepository()
    {
        filePath = "database/rescueTeams.txt";
        rebuildCache();
    }

    void RescueTeamRepository::rebuildCache()
    {
        teamCache.clear();
        auto teams = getAll();
        for (const auto& t : teams)
        {
            teamCache.add(t.getId(), t);
        }
    }

    Entities::RescueTeam RescueTeamRepository::parse(const std::string& line) const
    {
        Security::XORCipher cipher;
        std::string decrypted = cipher.decrypt(line);
        std::string dataToParse = decrypted.empty() ? line : decrypted;

        std::stringstream ss(dataToParse);
        std::string id, teamName, leaderName, location, members, available, tenantId;
        std::getline(ss, id, ',');
        std::getline(ss, teamName, ',');
        std::getline(ss, leaderName, ',');
        std::getline(ss, location, ',');
        std::getline(ss, members, ',');
        std::getline(ss, available, ',');
        std::getline(ss, tenantId);

        return Entities::RescueTeam(
            Core::safeStoi(id),
            teamName, leaderName, location,
            Core::safeStoi(members),
            Core::safeStob(available),
            tenantId
        );
    }

    bool RescueTeamRepository::add(const Entities::RescueTeam& team)
    {
        Security::XORCipher cipher;
        std::string encrypted = cipher.encrypt(team.toString());
        bool ok = fileManager.appendFile(filePath, encrypted + "\n");
        if (ok)
        {
            teamCache.add(team.getId(), team);
        }
        return ok;
    }

    bool RescueTeamRepository::update(const Entities::RescueTeam& team)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (auto& t : all)
        {
            if (t.getId() == team.getId())
            {
                t = team;
                found = true;
            }
            data += cipher.encrypt(t.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            teamCache.add(team.getId(), team);
        }
        return ok;
    }

    bool RescueTeamRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (const auto& t : all)
        {
            if (t.getId() == id)
            {
                found = true;
                continue;
            }
            data += cipher.encrypt(t.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            teamCache.remove(id);
        }
        return ok;
    }

    bool RescueTeamRepository::getById(int id, Entities::RescueTeam& team)
    {
        if (teamCache.get(id, team))
            return true;

        auto all = getAll();
        for (const auto& t : all)
        {
            if (t.getId() == id)
            {
                team = t;
                teamCache.add(id, t);
                return true;
            }
        }
        return false;
    }

    std::vector<Entities::RescueTeam> RescueTeamRepository::getAll()
    {
        std::vector<Entities::RescueTeam> teams;
        std::vector<std::string> lines = fileManager.readLines(filePath);
        for (const auto& line : lines)
        {
            if (!line.empty())
                teams.push_back(parse(line));
        }
        return teams;
    }

    std::vector<Entities::RescueTeam> RescueTeamRepository::getByTenant(const std::string& tenantId)
    {
        std::vector<Entities::RescueTeam> result;
        auto all = getAll();
        for (const auto& t : all)
        {
            if (t.getTenantId() == tenantId || tenantId == "ALL")
                result.push_back(t);
        }
        return result;
    }
}
}