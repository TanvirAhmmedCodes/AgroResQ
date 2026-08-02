#include "RescueTeamRepository.h"

#include <fstream>
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{

RescueTeamRepository::RescueTeamRepository()
{
    filePath = "database/rescueTeams.txt";
}

std::string RescueTeamRepository::serialize(
    const Entities::RescueTeam& team)
{
    return team.toString();
}

Entities::RescueTeam RescueTeamRepository::parse(
    const std::string& line)
{
    std::stringstream stream(line);

    std::string id;
    std::string teamName;
    std::string leaderName;
    std::string location;
    std::string members;
    std::string available;

    getline(stream,id,',');
    getline(stream,teamName,',');
    getline(stream,leaderName,',');
    getline(stream,location,',');
    getline(stream,members,',');
    getline(stream,available,',');

    return Entities::RescueTeam(
        std::stoi(id),
        teamName,
        leaderName,
        location,
        std::stoi(members),
        available == "1");
}

bool RescueTeamRepository::add(
    const Entities::RescueTeam& team)
{
    std::ofstream file(
        filePath,
        std::ios::app);

    if(!file)
        return false;

    file
        << serialize(team)
        << "\n";

    return true;
}

std::vector<Entities::RescueTeam>
RescueTeamRepository::getAll()
{
    std::vector<Entities::RescueTeam> teams;

    std::ifstream file(filePath);

    if(!file)
        return teams;

    std::string line;

    while(getline(file,line))
    {
        if(!line.empty())
        {
            teams.push_back(
                parse(line));
        }
    }

    return teams;
}

bool RescueTeamRepository::getById(
    int id,
    Entities::RescueTeam& team)
{
    auto teams = getAll();

    for(auto& item : teams)
    {
        if(item.getId() == id)
        {
            team = item;
            return true;
        }
    }

    return false;
}

bool RescueTeamRepository::update(
    const Entities::RescueTeam& team)
{
    auto teams = getAll();

    bool updated = false;

    for(auto& item : teams)
    {
        if(item.getId() == team.getId())
        {
            item = team;
            updated = true;
        }
    }

    if(!updated)
        return false;

    std::ofstream file(filePath);

    for(auto& item : teams)
    {
        file
            << serialize(item)
            << "\n";
    }

    return true;
}

bool RescueTeamRepository::remove(
    int id)
{
    auto teams = getAll();

    std::vector<Entities::RescueTeam> updatedList;

    bool removed = false;

    for(auto& item : teams)
    {
        if(item.getId() == id)
        {
            removed = true;
        }
        else
        {
            updatedList.push_back(item);
        }
    }

    if(!removed)
        return false;

    std::ofstream file(filePath);

    for(auto& item : updatedList)
    {
        file
            << serialize(item)
            << "\n";
    }

    return true;
}

}
}