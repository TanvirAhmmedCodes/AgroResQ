#include "SoilMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/agriculture/SoilRepository.h"
#include <iomanip>
#include <iostream>

namespace AgroResQ
{
namespace UI
{

SoilMenu::SoilMenu() = default;

void SoilMenu::show()
{
    int choice;
    do
    {
        std::cout << "\n=========================================\n";
        std::cout << "             SOIL MANAGEMENT\n";
        std::cout << "=========================================\n";
        std::cout << "1. Add Soil Data\n";
        std::cout << "2. View Soil Data\n";
        std::cout << "3. Search Soil\n";
        std::cout << "4. Update Soil\n";
        std::cout << "5. Delete Soil\n";
        std::cout << "0. Back\n";
        std::cout << "=========================================\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
        case 1: addSoil(); break;
        case 2: viewAllSoils(); break;
        case 3: searchSoil(); break;
        case 4: updateSoil(); break;
        case 5: deleteSoil(); break;
        case 0: break;
        default: std::cout << "\nInvalid Choice.\n";
        }
    } while(choice != 0);
}

void SoilMenu::addSoil()
{
    std::string farmId, soilType;
    double phLevel, moisture;
    std::cout << "\n\t\t\t\t\t\tFarm ID: ";
    std::cin >> farmId;
    std::cout << "\t\t\t\t\t\tPH Level (0-14): ";
    std::cin >> phLevel;
    std::cout << "\t\t\t\t\t\tMoisture Percentage: ";
    std::cin >> moisture;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tSoil Type: ";
    std::getline(std::cin, soilType);
    if(soilService.addSoil(farmId, phLevel, moisture, soilType))
        std::cout << "\n\t\t\t\t\t\tSoil Data Added Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tFailed To Add Soil Data.\n";
}

void SoilMenu::viewAllSoils()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Soil> soils;
    if (Core::AuthManager::isAdmin())
        soils = soilService.getAllSoils();
    else {
        Repositories::SoilRepository repo;
        soils = repo.getByTenant(currentTenant);
    }
    if(soils.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Soil Data Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t============================================================\n";
    std::cout << "\t\t\t\t\t\tID\tFarm\t\tPH\t\tMoisture\tType\n";
    std::cout << "\t\t\t\t\t\t============================================================\n";
    for(const auto& soil : soils) {
        std::cout << "\t\t\t\t\t\t" << soil.getId() << "\t"
                  << soil.getFarmId() << "\t\t"
                  << soil.getPhLevel() << "\t\t"
                  << soil.getMoisture() << "\t\t"
                  << soil.getSoilType() << "\n";
    }
}

void SoilMenu::searchSoil()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tEnter Soil ID: ";
    std::cin >> id;
    Entities::Soil soil;
    if(soilService.searchSoil(id, soil)) {
        std::cout << "\n\t\t\t\t\t\tID        : " << soil.getId();
        std::cout << "\n\t\t\t\t\t\tFarm ID   : " << soil.getFarmId();
        std::cout << "\n\t\t\t\t\t\tPH Level  : " << soil.getPhLevel();
        std::cout << "\n\t\t\t\t\t\tMoisture  : " << soil.getMoisture();
        std::cout << "\n\t\t\t\t\t\tSoil Type : " << soil.getSoilType() << "\n";
    } else {
        std::cout << "\n\t\t\t\t\t\tSoil Data Not Found.\n";
    }
}

void SoilMenu::updateSoil()
{
    int id;
    std::string farmId, soilType;
    double phLevel, moisture;
    std::cout << "\n\t\t\t\t\t\tSoil ID: ";
    std::cin >> id;
    std::cout << "\t\t\t\t\t\tFarm ID: ";
    std::cin >> farmId;
    std::cout << "\t\t\t\t\t\tPH Level: ";
    std::cin >> phLevel;
    std::cout << "\t\t\t\t\t\tMoisture: ";
    std::cin >> moisture;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tSoil Type: ";
    std::getline(std::cin, soilType);
    if(soilService.updateSoil(id, farmId, phLevel, moisture, soilType))
        std::cout << "\n\t\t\t\t\t\tUpdated Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tUpdate Failed.\n";
}

void SoilMenu::deleteSoil()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tSoil ID: ";
    std::cin >> id;
    if(soilService.deleteSoil(id))
        std::cout << "\n\t\t\t\t\t\tDeleted Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tDelete Failed.\n";
}

}
}