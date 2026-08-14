#include "VictimMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/victim/VictimRepository.h"
#include <iomanip>
#include <iostream>

namespace AgroResQ
{
namespace UI
{

VictimMenu::VictimMenu() = default;

void VictimMenu::show()
{
    int choice;
    do
    {
        std::cout << "\n=========================================\n";
        std::cout << "            VICTIM MANAGEMENT\n";
        std::cout << "=========================================\n";
        std::cout << "1. Add Victim\n";
        std::cout << "2. View Victims\n";
        std::cout << "3. Search Victim\n";
        std::cout << "4. Update Victim\n";
        std::cout << "5. Delete Victim\n";
        std::cout << "6. Search Family\n";
        std::cout << "7. Missing Victims\n";
        std::cout << "8. Assign Shelter\n";
        std::cout << "9. Process Next Rescue\n";
        std::cout << "0. Back\n";
        std::cout << "=========================================\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1: addVictim(); break;
        case 2: viewAllVictims(); break;
        case 3: searchVictim(); break;
        case 4: updateVictim(); break;
        case 5: deleteVictim(); break;
        case 6: searchFamily(); break;
        case 7: viewMissingVictims(); break;
        case 8: assignShelter(); break;
        case 9: processNextRescue(); break;
        case 0: break;
        default: std::cout << "\nInvalid Choice.\n";
        }
    } while (choice != 0);
}

void VictimMenu::addVictim()
{
    std::string name, gender, address, healthStatus;
    int age, familyId, priorityScore, shelterId;
    char vulnerableInput, disabledInput, rescuedInput, reliefInput, missingInput;
    bool vulnerable, disabled, rescued, reliefReceived, missing;

    std::cin.ignore();
    std::cout << "\n\t\t\t\t\t\tName: ";
    std::getline(std::cin, name);
    std::cout << "\t\t\t\t\t\tAge: ";
    std::cin >> age;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tGender: ";
    std::getline(std::cin, gender);
    std::cout << "\t\t\t\t\t\tAddress: ";
    std::getline(std::cin, address);
    std::cout << "\t\t\t\t\t\tVulnerable? (y/n): ";
    std::cin >> vulnerableInput;
    std::cout << "\t\t\t\t\t\tFamily ID: ";
    std::cin >> familyId;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tHealth Status: ";
    std::getline(std::cin, healthStatus);
    std::cout << "\t\t\t\t\t\tDisabled? (y/n): ";
    std::cin >> disabledInput;
    std::cout << "\t\t\t\t\t\tRescued? (y/n): ";
    std::cin >> rescuedInput;
    std::cout << "\t\t\t\t\t\tRelief Received? (y/n): ";
    std::cin >> reliefInput;
    std::cout << "\t\t\t\t\t\tMissing? (y/n): ";
    std::cin >> missingInput;
    std::cout << "\t\t\t\t\t\tPriority Score: ";
    std::cin >> priorityScore;
    std::cout << "\t\t\t\t\t\tShelter ID: ";
    std::cin >> shelterId;

    vulnerable = (vulnerableInput == 'y' || vulnerableInput == 'Y');
    disabled = (disabledInput == 'y' || disabledInput == 'Y');
    rescued = (rescuedInput == 'y' || rescuedInput == 'Y');
    reliefReceived = (reliefInput == 'y' || reliefInput == 'Y');
    missing = (missingInput == 'y' || missingInput == 'Y');

    if (victimService.addVictim(name, age, gender, address, vulnerable, familyId,
        healthStatus, disabled, rescued, reliefReceived, missing,
        priorityScore, shelterId))
    {
        auto victims = victimService.getAllVictims();
        if (!victims.empty())
        {
            int lastId = victims.back().getId();
            if (!rescued && !missing)
            {
                rescueQueue.push(lastId);
                std::cout << "\n\t\t\t\t\t\tVictim Added to Rescue Queue.\n";
            }
        }
        std::cout << "\n\t\t\t\t\t\tVictim Added Successfully.\n";
    }
    else
    {
        std::cout << "\n\t\t\t\t\t\tFailed To Add Victim.\n";
    }
}

void VictimMenu::viewAllVictims()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Victim> victims;
    if (Core::AuthManager::isAdmin())
        victims = victimService.getAllVictims();
    else {
        Repositories::VictimRepository repo;
        victims = repo.getByTenant(currentTenant);
    }
    if (victims.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Victim Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t====================================================================\n";
    std::cout << "\t\t\t\t\t\tID\tName\t\t\tAge\tGender\t\tAddress\t\tPriority\n";
    std::cout << "\t\t\t\t\t\t====================================================================\n";
    for (auto& victim : victims) {
        std::cout << "\t\t\t\t\t\t" << victim.getId() << "\t"
                  << victim.getName() << "\t\t\t"
                  << victim.getAge() << "\t"
                  << victim.getGender() << "\t\t"
                  << victim.getAddress() << "\t\t"
                  << (victim.isVulnerable() ? "High" : "Normal") << "\n";
    }
}

void VictimMenu::searchVictim()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tVictim ID: ";
    std::cin >> id;

    Entities::Victim victim;
    if (victimService.searchVictim(id, victim))
    {
        std::cout << "\n\t\t\t\t\t\tID          : " << victim.getId();
        std::cout << "\n\t\t\t\t\t\tName        : " << victim.getName();
        std::cout << "\n\t\t\t\t\t\tAge         : " << victim.getAge();
        std::cout << "\n\t\t\t\t\t\tGender      : " << victim.getGender();
        std::cout << "\n\t\t\t\t\t\tAddress     : " << victim.getAddress();
        std::cout << "\n\t\t\t\t\t\tVulnerable  : " << (victim.isVulnerable() ? "Yes" : "No");
        std::cout << "\n\t\t\t\t\t\tMissing     : " << (victim.isMissing() ? "Yes" : "No");
        std::cout << "\n\t\t\t\t\t\tRescued     : " << (victim.isRescued() ? "Yes" : "No") << "\n";
    }
    else
    {
        std::cout << "\n\t\t\t\t\t\tVictim Not Found.\n";
    }
}

void VictimMenu::updateVictim()
{
    int id, age, familyId, priorityScore, shelterId;
    std::string name, gender, address, healthStatus;
    char vulnerableInput, disabledInput, rescuedInput, reliefInput, missingInput;
    bool vulnerable, disabled, rescued, reliefReceived, missing;

    std::cout << "\n\t\t\t\t\t\tVictim ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tName: ";
    std::getline(std::cin, name);
    std::cout << "\t\t\t\t\t\tAge: ";
    std::cin >> age;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tGender: ";
    std::getline(std::cin, gender);
    std::cout << "\t\t\t\t\t\tAddress: ";
    std::getline(std::cin, address);
    std::cout << "\t\t\t\t\t\tVulnerable? (y/n): ";
    std::cin >> vulnerableInput;
    std::cout << "\t\t\t\t\t\tFamily ID: ";
    std::cin >> familyId;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tHealth Status: ";
    std::getline(std::cin, healthStatus);
    std::cout << "\t\t\t\t\t\tDisabled? (y/n): ";
    std::cin >> disabledInput;
    std::cout << "\t\t\t\t\t\tRescued? (y/n): ";
    std::cin >> rescuedInput;
    std::cout << "\t\t\t\t\t\tRelief Received? (y/n): ";
    std::cin >> reliefInput;
    std::cout << "\t\t\t\t\t\tMissing? (y/n): ";
    std::cin >> missingInput;
    std::cout << "\t\t\t\t\t\tPriority Score: ";
    std::cin >> priorityScore;
    std::cout << "\t\t\t\t\t\tShelter ID: ";
    std::cin >> shelterId;

    vulnerable = (vulnerableInput == 'y' || vulnerableInput == 'Y');
    disabled = (disabledInput == 'y' || disabledInput == 'Y');
    rescued = (rescuedInput == 'y' || rescuedInput == 'Y');
    reliefReceived = (reliefInput == 'y' || reliefInput == 'Y');
    missing = (missingInput == 'y' || missingInput == 'Y');

    if (victimService.updateVictim(id, name, age, gender, address, vulnerable, familyId,
        healthStatus, disabled, rescued, reliefReceived, missing,
        priorityScore, shelterId))
    {
        std::cout << "\n\t\t\t\t\t\tUpdated Successfully.\n";
    }
    else
    {
        std::cout << "\n\t\t\t\t\t\tUpdate Failed.\n";
    }
}

void VictimMenu::deleteVictim()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tVictim ID: ";
    std::cin >> id;

    if (victimService.deleteVictim(id))
    {
        std::cout << "\n\t\t\t\t\t\tDeleted Successfully.\n";
    }
    else
    {
        std::cout << "\n\t\t\t\t\t\tDelete Failed.\n";
    }
}

void VictimMenu::searchFamily()
{
    int familyId;
    std::cout << "\n\t\t\t\t\t\tFamily ID: ";
    std::cin >> familyId;

    auto victims = victimService.getVictimsByFamily(familyId);
    if (victims.empty())
    {
        std::cout << "\n\t\t\t\t\t\tNo Family Members Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\tFamily Members:\n";
    for (const auto& victim : victims)
    {
        std::cout << "\t\t\t\t\t\tID: " << victim.getId()
                  << " | Name: " << victim.getName()
                  << " | Age: " << victim.getAge() << "\n";
    }
}

void VictimMenu::viewMissingVictims()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Victim> victims;
    if (Core::AuthManager::isAdmin())
        victims = victimService.getMissingVictims();
    else {
        Repositories::VictimRepository repo;
        auto all = repo.getByTenant(currentTenant);
        for(auto& v : all) {
            if(v.isMissing()) victims.push_back(v);
        }
    }
    if(victims.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Missing Victims.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\tMissing Victims:\n";
    for (const auto& victim : victims)
    {
        std::cout << "\t\t\t\t\t\tID: " << victim.getId()
                  << " | Name: " << victim.getName()
                  << " | Location: " << victim.getAddress() << "\n";
    }
}

void VictimMenu::assignShelter()
{
    int victimId, shelterId;
    std::cout << "\n\t\t\t\t\t\tVictim ID: ";
    std::cin >> victimId;
    std::cout << "\t\t\t\t\t\tShelter ID: ";
    std::cin >> shelterId;

    if (victimService.assignShelter(victimId, shelterId))
    {
        std::cout << "\n\t\t\t\t\t\tShelter Assigned Successfully.\n";
    }
    else
    {
        std::cout << "\n\t\t\t\t\t\tAssignment Failed.\n";
    }
}

void VictimMenu::processNextRescue()
{
    if (rescueQueue.isEmpty())
    {
        std::cout << "\n\t\t\t\t\t\tNo Victims in Rescue Queue.\n";
        return;
    }

    int victimId = rescueQueue.top();
    rescueQueue.pop();

    Entities::Victim victim;
    if (!victimService.searchVictim(victimId, victim))
    {
        std::cout << "\n\t\t\t\t\t\tVictim Not Found. Removing from Queue.\n";
        return;
    }

    std::cout << "\n\t\t\t\t\t\t========== PROCESSING RESCUE ==========\n";
    std::cout << "\t\t\t\t\t\tVictim ID    : " << victim.getId() << "\n";
    std::cout << "\t\t\t\t\t\tName         : " << victim.getName() << "\n";
    std::cout << "\t\t\t\t\t\tAge          : " << victim.getAge() << "\n";
    std::cout << "\t\t\t\t\t\tAddress      : " << victim.getAddress() << "\n";
    std::cout << "\t\t\t\t\t\tPriority     : " << victim.getPriorityScore() << "\n";
    std::cout << "\t\t\t\t\t\tVulnerable   : " << (victim.isVulnerable() ? "Yes" : "No") << "\n";
    std::cout << "\t\t\t\t\t\tDisabled     : " << (victim.isDisabled() ? "Yes" : "No") << "\n";
    std::cout << "\t\t\t\t\t\tHealth Status: " << victim.getHealthStatus() << "\n";

    char confirm;
    std::cout << "\n\t\t\t\t\t\tMark as Rescued? (y/n): ";
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y')
    {
        victim.setRescued(true);
        victimService.updateVictim(
            victim.getId(),
            victim.getName(),
            victim.getAge(),
            victim.getGender(),
            victim.getAddress(),
            victim.isVulnerable(),
            victim.getFamilyId(),
            victim.getHealthStatus(),
            victim.isDisabled(),
            true,
            victim.hasReliefReceived(),
            victim.isMissing(),
            victim.getPriorityScore(),
            victim.getShelterId()
        );
        std::cout << "\n\t\t\t\t\t\tVictim Marked as Rescued.\n";
    }
    else
    {
        std::cout << "\n\t\t\t\t\t\tRescue Cancelled. Victim remains in queue.\n";
        rescueQueue.push(victimId);
    }

    std::cout << "\t\t\t\t\t\tRemaining in Queue: " << rescueQueue.size() << "\n";
    std::cout << "\t\t\t\t\t\t=========================================\n";
}

}
}