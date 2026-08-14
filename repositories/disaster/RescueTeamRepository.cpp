#include "RescueTeamRepository.h"
#include "../../core/StringHelper.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    RescueTeamRepository::RescueTeamRepository()
    {
        filePath = "database/rescueTeams.txt";
    }

    Entities::RescueTeam RescueTeamRepository::parse(const std::string& line) const
    {
        std::stringstream ss(line);
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
        return fileManager.appendFile(filePath, team.toString() + "\n");
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

    bool RescueTeamRepository::getById(int id, Entities::RescueTeam& team)
    {
        auto all = getAll();
        for (const auto& t : all)
        {
            if (t.getId() == id)
            {
                team = t;
                return true;
            }
        }
        return false;
    }

    bool RescueTeamRepository::update(const Entities::RescueTeam& team)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (auto& t : all)
        {
            if (t.getId() == team.getId())
            {
                t = team;
                found = true;
            }
            data += t.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    bool RescueTeamRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (const auto& t : all)
        {
            if (t.getId() == id)
            {
                found = true;
                continue;
            }
            data += t.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
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