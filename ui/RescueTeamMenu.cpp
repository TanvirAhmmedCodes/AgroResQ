#include "RescueTeamMenu.h"

#include <iostream>
#include <iomanip>

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
        std::cout
        << "\n=========================================\n";

        std::cout
        << "        RESCUE TEAM MANAGEMENT\n";

        std::cout
        << "=========================================\n";

        std::cout
        << "1. Add Rescue Team\n";
        std::cout
        << "2. View Rescue Teams\n";
        std::cout
        << "3. Search Rescue Team\n";
        std::cout
        << "4. Update Rescue Team\n";
        std::cout
        << "5. Delete Rescue Team\n";
        std::cout
        << "0. Back\n";

        std::cout
        << "=========================================\n";

        std::cout
        << "Enter Choice: ";

        std::cin >> choice;

        switch(choice)
        {
        case 1:
            addRescueTeam();
            break;

        case 2:
            viewAllRescueTeams();
            break;

        case 3:
            searchRescueTeam();
            break;

        case 4:
            updateRescueTeam();
            break;

        case 5:
            deleteRescueTeam();
            break;

        case 0:
            break;

        default:
            std::cout
            << "\nInvalid Choice.\n";
        }

    }
    while(choice != 0);
}

void RescueTeamMenu::addRescueTeam()
{
    std::string teamName;
    std::string leaderName;
    std::string location;

    int members;

    char availableInput;

    bool available;

    std::cin.ignore();

    std::cout << "\nTeam Name: ";
    getline(std::cin, teamName);

    std::cout << "Leader Name: ";
    getline(std::cin, leaderName);

    std::cout << "Location: ";
    getline(std::cin, location);

    std::cout << "Members: ";
    std::cin >> members;

    std::cout << "Available (y/n): ";
    std::cin >> availableInput;

    available =
        availableInput == 'y' ||
        availableInput == 'Y';

    if(rescueTeamService.addRescueTeam(
        teamName,
        leaderName,
        location,
        members,
        available))
    {
        std::cout
        << "\nRescue Team Added Successfully.\n";
    }
    else
    {
        std::cout
        << "\nFailed To Add Rescue Team.\n";
    }
}

void RescueTeamMenu::viewAllRescueTeams()
{
    auto teams =
        rescueTeamService.getAllRescueTeams();

    if(teams.empty())
    {
        std::cout
        << "\nNo Rescue Team Found.\n";
        return;
    }

    std::cout
    << "\n=========================================================================\n";

    std::cout
    << std::left
    << std::setw(5) << "ID"
    << std::setw(20) << "Team"
    << std::setw(20) << "Leader"
    << std::setw(18) << "Location"
    << std::setw(10) << "Members"
    << std::setw(10) << "Status"
    << "\n";

    std::cout
    << "=========================================================================\n";

    for(auto& team : teams)
    {
        std::cout
        << std::left
        << std::setw(5) << team.getId()
        << std::setw(20) << team.getTeamName()
        << std::setw(20) << team.getLeaderName()
        << std::setw(18) << team.getLocation()
        << std::setw(10) << team.getMembers()
        << std::setw(10)
        << (team.isAvailable() ? "Ready" : "Busy")
        << "\n";
    }
}

void RescueTeamMenu::searchRescueTeam()
{
    int id;

    std::cout
    << "\nRescue Team ID: ";

    std::cin >> id;

    Entities::RescueTeam team;

    if(rescueTeamService.searchRescueTeam(
        id,
        team))
    {
        std::cout
        << "\nID          : "
        << team.getId();

        std::cout
        << "\nTeam Name   : "
        << team.getTeamName();

        std::cout
        << "\nLeader      : "
        << team.getLeaderName();

        std::cout
        << "\nLocation    : "
        << team.getLocation();

        std::cout
        << "\nMembers     : "
        << team.getMembers();

        std::cout
        << "\nAvailable   : "
        << (team.isAvailable() ? "Yes" : "No")
        << "\n";
    }
    else
    {
        std::cout
        << "\nRescue Team Not Found.\n";
    }
}

void RescueTeamMenu::updateRescueTeam()
{
    int id;
    int members;

    std::string teamName;
    std::string leaderName;
    std::string location;

    char availableInput;

    bool available;

    std::cout
    << "\nRescue Team ID: ";

    std::cin >> id;

    std::cin.ignore();

    std::cout << "Team Name: ";
    getline(std::cin, teamName);

    std::cout << "Leader Name: ";
    getline(std::cin, leaderName);

    std::cout << "Location: ";
    getline(std::cin, location);

    std::cout << "Members: ";
    std::cin >> members;

    std::cout << "Available (y/n): ";
    std::cin >> availableInput;

    available =
        availableInput == 'y' ||
        availableInput == 'Y';

    if(rescueTeamService.updateRescueTeam(
        id,
        teamName,
        leaderName,
        location,
        members,
        available))
    {
        std::cout
        << "\nUpdated Successfully.\n";
    }
    else
    {
        std::cout
        << "\nUpdate Failed.\n";
    }
}

void RescueTeamMenu::deleteRescueTeam()
{
    int id;

    std::cout
    << "\nRescue Team ID: ";

    std::cin >> id;

    if(rescueTeamService.deleteRescueTeam(id))
    {
        std::cout
        << "\nDeleted Successfully.\n";
    }
    else
    {
        std::cout
        << "\nDelete Failed.\n";
    }
}

}
}