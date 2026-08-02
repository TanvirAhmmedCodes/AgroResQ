#pragma once

#include "../services/RescueTeamService.h"

namespace AgroResQ
{
namespace UI
{

class RescueTeamMenu
{
private:

    Services::RescueTeamService rescueTeamService;

    void addRescueTeam();

    void viewAllRescueTeams();

    void searchRescueTeam();

    void updateRescueTeam();

    void deleteRescueTeam();

public:

    RescueTeamMenu();

    void show();
};

}
}