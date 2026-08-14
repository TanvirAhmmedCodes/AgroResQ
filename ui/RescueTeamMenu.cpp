#include "RescueTeamMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/disaster/RescueTeamRepository.h"
#include <iomanip>
#include <iostream>

namespace AgroResQ
{
namespace UI
{

RescueTeamMenu::RescueTeamMenu() = default;

void RescueTeamMenu::show()
{
    int choice;
    do
    {
        std::cout << "\n=========================================\n";
        std::cout << "        RESCUE TEAM MANAGEMENT\n";
        std::cout << "=========================================\n";
        std::cout << "1. Add Rescue Team\n";
        std::cout << "2. View Rescue Teams\n";
        std::cout << "3. Search Rescue Team\n";
        std::cout << "4. Update Rescue Team\n";
        std::cout << "5. Delete Rescue Team\n";
        std::cout << "0. Back\n";
        std::cout << "=========================================\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
        case 1: addRescueTeam(); break;
        case 2: viewAllRescueTeams(); break;
        case 3: searchRescueTeam(); break;
        case 4: updateRescueTeam(); break;
        case 5: deleteRescueTeam(); break;
        case 0: break;
        default: std::cout << "\nInvalid Choice.\n";
        }
    } while(choice != 0);
}

void RescueTeamMenu::addRescueTeam()
{
    std::string teamName, leaderName, location;
    int members;
    char availableInput;
    bool available;
    std::cin.ignore();
    std::cout << "\n\t\t\t\t\t\tTeam Name: ";
    std::getline(std::cin, teamName);
    std::cout << "\t\t\t\t\t\tLeader Name: ";
    std::getline(std::cin, leaderName);
    std::cout << "\t\t\t\t\t\tLocation: ";
    std::getline(std::cin, location);
    std::cout << "\t\t\t\t\t\tMembers: ";
    std::cin >> members;
    std::cout << "\t\t\t\t\t\tAvailable (y/n): ";
    std::cin >> availableInput;
    available = (availableInput == 'y' || availableInput == 'Y');
    if(rescueTeamService.addRescueTeam(teamName, leaderName, location, members, available))
        std::cout << "\n\t\t\t\t\t\tRescue Team Added Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tFailed To Add Rescue Team.\n";
}

void RescueTeamMenu::viewAllRescueTeams()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::RescueTeam> teams;
    if (Core::AuthManager::isAdmin())
        teams = rescueTeamService.getAllRescueTeams();
    else {
        Repositories::RescueTeamRepository repo;
        teams = repo.getByTenant(currentTenant);
    }
    if(teams.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Rescue Team Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t=========================================================================\n";
    std::cout << "\t\t\t\t\t\tID\tTeam\t\t\tLeader\t\t\tLocation\t\tMembers\tStatus\n";
    std::cout << "\t\t\t\t\t\t=========================================================================\n";
    for(auto& t : teams) {
        std::cout << "\t\t\t\t\t\t" << t.getId() << "\t"
                  << t.getTeamName() << "\t\t\t"
                  << t.getLeaderName() << "\t\t\t"
                  << t.getLocation() << "\t\t"
                  << t.getMembers() << "\t"
                  << (t.isAvailable() ? "Ready" : "Busy") << "\n";
    }
}

void RescueTeamMenu::searchRescueTeam()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tRescue Team ID: ";
    std::cin >> id;
    Entities::RescueTeam team;
    if(rescueTeamService.searchRescueTeam(id, team)) {
        std::cout << "\n\t\t\t\t\t\tID          : " << team.getId();
        std::cout << "\n\t\t\t\t\t\tTeam Name   : " << team.getTeamName();
        std::cout << "\n\t\t\t\t\t\tLeader      : " << team.getLeaderName();
        std::cout << "\n\t\t\t\t\t\tLocation    : " << team.getLocation();
        std::cout << "\n\t\t\t\t\t\tMembers     : " << team.getMembers();
        std::cout << "\n\t\t\t\t\t\tAvailable   : " << (team.isAvailable() ? "Yes" : "No") << "\n";
    } else {
        std::cout << "\n\t\t\t\t\t\tRescue Team Not Found.\n";
    }
}

void RescueTeamMenu::updateRescueTeam()
{
    int id, members;
    std::string teamName, leaderName, location;
    char availableInput;
    bool available;
    std::cout << "\n\t\t\t\t\t\tRescue Team ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tTeam Name: ";
    std::getline(std::cin, teamName);
    std::cout << "\t\t\t\t\t\tLeader Name: ";
    std::getline(std::cin, leaderName);
    std::cout << "\t\t\t\t\t\tLocation: ";
    std::getline(std::cin, location);
    std::cout << "\t\t\t\t\t\tMembers: ";
    std::cin >> members;
    std::cout << "\t\t\t\t\t\tAvailable (y/n): ";
    std::cin >> availableInput;
    available = (availableInput == 'y' || availableInput == 'Y');
    if(rescueTeamService.updateRescueTeam(id, teamName, leaderName, location, members, available))
        std::cout << "\n\t\t\t\t\t\tUpdated Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tUpdate Failed.\n";
}

void RescueTeamMenu::deleteRescueTeam()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tRescue Team ID: ";
    std::cin >> id;
    if(rescueTeamService.deleteRescueTeam(id))
        std::cout << "\n\t\t\t\t\t\tDeleted Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tDelete Failed.\n";
}

}
}