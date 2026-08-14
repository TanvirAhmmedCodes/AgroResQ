#include "RescueTeamService.h"
#include "../core/AuthManager.h"

namespace AgroResQ
{
namespace Services
{

RescueTeamService::RescueTeamService() = default;

bool RescueTeamService::addRescueTeam(
    const std::string& teamName,
    const std::string& leaderName,
    const std::string& location,
    int members,
    bool available)
{
    if(teamName.empty())
        return false;

    if(leaderName.empty())
        return false;

    if(members <= 0)
        return false;

    int id = idGenerator.generateNextId("database/rescueTeams.txt");
    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::RescueTeam team(
        id,
        teamName,
        leaderName,
        location,
        members,
        available,
        tenantId);

    return rescueTeamRepository.add(team);
}

bool RescueTeamService::updateRescueTeam(
    int id,
    const std::string& teamName,
    const std::string& leaderName,
    const std::string& location,
    int members,
    bool available)
{
    if(teamName.empty())
        return false;

    if(leaderName.empty())
        return false;

    if(members <= 0)
        return false;

    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::RescueTeam team(
        id,
        teamName,
        leaderName,
        location,
        members,
        available,
        tenantId);

    return rescueTeamRepository.update(team);
}

bool RescueTeamService::deleteRescueTeam(
    int id)
{
    return rescueTeamRepository.remove(id);
}

bool RescueTeamService::searchRescueTeam(
    int id,
    Entities::RescueTeam& team)
{
    return rescueTeamRepository.getById(id, team);
}

std::vector<Entities::RescueTeam>
RescueTeamService::getAllRescueTeams()
{
    return rescueTeamRepository.getAll();
}

}
}