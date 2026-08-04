#include "ShelterMenu.h"

#include <iostream>
#include <iomanip>

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
        case 1:
            addShelter();
            break;

        case 2:
            viewAllShelters();
            break;

        case 3:
            searchShelter();
            break;

        case 4:
            updateShelter();
            break;

        case 5:
            deleteShelter();
            break;

        case 6:
            viewAvailableShelters();
            break;

        case 0:
            break;

        default:
            std::cout << "\nInvalid Choice.\n";
        }

    } while(choice != 0);
}

void ShelterMenu::addShelter()
{
    std::string name;
    std::string location;
    int capacity;
    int occupied;

    std::cin.ignore();

    std::cout << "\nShelter Name: ";
    getline(std::cin, name);

    std::cout << "Location: ";
    getline(std::cin, location);

    std::cout << "Capacity: ";
    std::cin >> capacity;

    std::cout << "Occupied: ";
    std::cin >> occupied;

    if(shelterService.addShelter(
        name,
        location,
        capacity,
        occupied))
    {
        std::cout << "\nShelter Added Successfully.\n";
    }
    else
    {
        std::cout << "\nFailed To Add Shelter.\n";
    }
}

void ShelterMenu::viewAllShelters()
{
    auto shelters =
        shelterService.getAllShelters();

    if(shelters.empty())
    {
        std::cout << "\nNo Shelter Found.\n";
        return;
    }

    std::cout << "\n====================================================================\n";

    std::cout
        << std::left
        << std::setw(5) << "ID"
        << std::setw(20) << "Name"
        << std::setw(20) << "Location"
        << std::setw(12) << "Capacity"
        << std::setw(12) << "Occupied"
        << "\n";

    std::cout << "====================================================================\n";

    for(auto& shelter : shelters)
    {
        std::cout
            << std::left
            << std::setw(5) << shelter.getId()
            << std::setw(20) << shelter.getName()
            << std::setw(20) << shelter.getLocation()
            << std::setw(12) << shelter.getCapacity()
            << std::setw(12) << shelter.getOccupied()
            << "\n";
    }
}

void ShelterMenu::searchShelter()
{
    int id;

    std::cout << "\nShelter ID: ";
    std::cin >> id;

    Entities::Shelter shelter;

    if(shelterService.searchShelter(
        id,
        shelter))
    {
        std::cout << "\nID        : " << shelter.getId();
        std::cout << "\nName      : " << shelter.getName();
        std::cout << "\nLocation  : " << shelter.getLocation();
        std::cout << "\nCapacity  : " << shelter.getCapacity();
        std::cout << "\nOccupied  : " << shelter.getOccupied() << "\n";
    }
    else
    {
        std::cout << "\nShelter Not Found.\n";
    }
}

void ShelterMenu::updateShelter()
{
    int id;
    std::string name;
    std::string location;
    int capacity;
    int occupied;

    std::cout << "\nShelter ID: ";
    std::cin >> id;

    std::cin.ignore();

    std::cout << "Name: ";
    getline(std::cin, name);

    std::cout << "Location: ";
    getline(std::cin, location);

    std::cout << "Capacity: ";
    std::cin >> capacity;

    std::cout << "Occupied: ";
    std::cin >> occupied;

    if(shelterService.updateShelter(
        id,
        name,
        location,
        capacity,
        occupied))
    {
        std::cout << "\nUpdated Successfully.\n";
    }
    else
    {
        std::cout << "\nUpdate Failed.\n";
    }
}

void ShelterMenu::deleteShelter()
{
    int id;

    std::cout << "\nShelter ID: ";
    std::cin >> id;

    if(shelterService.deleteShelter(id))
    {
        std::cout << "\nDeleted Successfully.\n";
    }
    else
    {
        std::cout << "\nDelete Failed.\n";
    }
}

void ShelterMenu::viewAvailableShelters()
{
    auto shelters =
        shelterService.getAvailableShelters();

    if(shelters.empty())
    {
        std::cout << "\nNo Available Shelter.\n";
        return;
    }

    std::cout << "\n================ AVAILABLE SHELTERS ================\n";

    for(auto& shelter : shelters)
    {
        std::cout
            << shelter.getId()
            << " | "
            << shelter.getName()
            << " | Available: "
            << shelter.getCapacity() - shelter.getOccupied()
            << "\n";
    }
}

}
}