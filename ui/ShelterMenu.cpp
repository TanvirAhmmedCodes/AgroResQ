#include "ShelterMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/disaster/ShelterRepository.h"
#include <iomanip>
#include <iostream>

namespace AgroResQ
{
namespace UI
{

ShelterMenu::ShelterMenu() = default;

void ShelterMenu::show()
{
    int choice;
    do
    {
        std::cout << "\n=========================================\n";
        std::cout << "          SHELTER MANAGEMENT\n";
        std::cout << "=========================================\n";
        std::cout << "1. Add Shelter\n";
        std::cout << "2. View Shelters\n";
        std::cout << "3. Search Shelter\n";
        std::cout << "4. Update Shelter\n";
        std::cout << "5. Delete Shelter\n";
        std::cout << "6. Available Shelters\n";
        std::cout << "0. Back\n";
        std::cout << "=========================================\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
        case 1: addShelter(); break;
        case 2: viewAllShelters(); break;
        case 3: searchShelter(); break;
        case 4: updateShelter(); break;
        case 5: deleteShelter(); break;
        case 6: viewAvailableShelters(); break;
        case 0: break;
        default: std::cout << "\nInvalid Choice.\n";
        }
    } while(choice != 0);
}

void ShelterMenu::addShelter()
{
    std::string name, location;
    int capacity, occupied;
    std::cin.ignore();
    std::cout << "\n\t\t\t\t\t\tShelter Name: ";
    std::getline(std::cin, name);
    std::cout << "\t\t\t\t\t\tLocation: ";
    std::getline(std::cin, location);
    std::cout << "\t\t\t\t\t\tCapacity: ";
    std::cin >> capacity;
    std::cout << "\t\t\t\t\t\tOccupied: ";
    std::cin >> occupied;
    if(shelterService.addShelter(name, location, capacity, occupied))
        std::cout << "\n\t\t\t\t\t\tShelter Added Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tFailed To Add Shelter.\n";
}

void ShelterMenu::viewAllShelters()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Shelter> shelters;
    if (Core::AuthManager::isAdmin())
        shelters = shelterService.getAllShelters();
    else {
        Repositories::ShelterRepository repo;
        shelters = repo.getByTenant(currentTenant);
    }
    if(shelters.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Shelter Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t====================================================================\n";
    std::cout << "\t\t\t\t\t\tID\tName\t\t\tLocation\t\tCapacity\tOccupied\n";
    std::cout << "\t\t\t\t\t\t====================================================================\n";
    for(auto& s : shelters) {
        std::cout << "\t\t\t\t\t\t" << s.getId() << "\t"
                  << s.getName() << "\t\t\t"
                  << s.getLocation() << "\t\t"
                  << s.getCapacity() << "\t\t"
                  << s.getOccupied() << "\n";
    }
}

void ShelterMenu::searchShelter()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tShelter ID: ";
    std::cin >> id;
    Entities::Shelter shelter;
    if(shelterService.searchShelter(id, shelter)) {
        std::cout << "\n\t\t\t\t\t\tID        : " << shelter.getId();
        std::cout << "\n\t\t\t\t\t\tName      : " << shelter.getName();
        std::cout << "\n\t\t\t\t\t\tLocation  : " << shelter.getLocation();
        std::cout << "\n\t\t\t\t\t\tCapacity  : " << shelter.getCapacity();
        std::cout << "\n\t\t\t\t\t\tOccupied  : " << shelter.getOccupied() << "\n";
    } else {
        std::cout << "\n\t\t\t\t\t\tShelter Not Found.\n";
    }
}

void ShelterMenu::updateShelter()
{
    int id, capacity, occupied;
    std::string name, location;
    std::cout << "\n\t\t\t\t\t\tShelter ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tName: ";
    std::getline(std::cin, name);
    std::cout << "\t\t\t\t\t\tLocation: ";
    std::getline(std::cin, location);
    std::cout << "\t\t\t\t\t\tCapacity: ";
    std::cin >> capacity;
    std::cout << "\t\t\t\t\t\tOccupied: ";
    std::cin >> occupied;
    if(shelterService.updateShelter(id, name, location, capacity, occupied))
        std::cout << "\n\t\t\t\t\t\tUpdated Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tUpdate Failed.\n";
}

void ShelterMenu::deleteShelter()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tShelter ID: ";
    std::cin >> id;
    if(shelterService.deleteShelter(id))
        std::cout << "\n\t\t\t\t\t\tDeleted Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tDelete Failed.\n";
}

void ShelterMenu::viewAvailableShelters()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Shelter> shelters;
    if (Core::AuthManager::isAdmin())
        shelters = shelterService.getAvailableShelters();
    else {
        Repositories::ShelterRepository repo;
        auto all = repo.getByTenant(currentTenant);
        for(auto& s : all) {
            if(s.getOccupied() < s.getCapacity())
                shelters.push_back(s);
        }
    }
    if(shelters.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Available Shelter.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t================ AVAILABLE SHELTERS ================\n";
    for(auto& s : shelters) {
        std::cout << "\t\t\t\t\t\t" << s.getId() << " | "
                  << s.getName() << " | Available: "
                  << s.getCapacity() - s.getOccupied() << "\n";
    }
}

}
}