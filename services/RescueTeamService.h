#pragma once

#include <vector>

#include "../core/IDGenerator.h"

#include "../entities/RescueTeam.h"

#include "../repositories/disaster/RescueTeamRepository.h"

namespace AgroResQ
{
namespace Services
{

class RescueTeamService
{
private:

    Repositories::RescueTeamRepository rescueTeamRepository;

    Core::IDGenerator idGenerator;

public:

    RescueTeamService();

    bool addRescueTeam(
        const std::string& teamName,
        const std::string& leaderName,
        const std::string& location,
        int members,
        bool available);

    bool updateRescueTeam(
        int id,
        const std::string& teamName,
        const std::string& leaderName,
        const std::string& location,
        int members,
        bool available);

    bool deleteRescueTeam(
        int id);

    bool searchRescueTeam(
        int id,
        Entities::RescueTeam& team);

    std::vector<Entities::RescueTeam> getAllRescueTeams();
};

}
}