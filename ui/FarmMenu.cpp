#include "FarmMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/agriculture/FarmRepository.h"
#include <iomanip>
#include <iostream>

namespace AgroResQ
{
namespace UI
{

FarmMenu::FarmMenu() = default;

void FarmMenu::show()
{
    int choice;
    do
    {
        std::cout << "\n=========================================\n";
        std::cout << "              FARM MANAGEMENT\n";
        std::cout << "=========================================\n";
        std::cout << "1. Add Farm\n";
        std::cout << "2. View Farms\n";
        std::cout << "3. Search Farm\n";
        std::cout << "4. Update Farm\n";
        std::cout << "5. Delete Farm\n";
        std::cout << "0. Back\n";
        std::cout << "=========================================\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1: addFarm(); break;
        case 2: viewAllFarms(); break;
        case 3: searchFarm(); break;
        case 4: updateFarm(); break;
        case 5: deleteFarm(); break;
        case 0: break;
        default: std::cout << "\nInvalid Choice.\n";
        }
    } while (choice != 0);
}

void FarmMenu::addFarm()
{
    std::string farmerName, location, soilType, cropName;
    double landArea;
    std::cin.ignore();
    std::cout << "\n\t\t\t\t\t\tFarmer Name: ";
    std::getline(std::cin, farmerName);
    std::cout << "\t\t\t\t\t\tLocation: ";
    std::getline(std::cin, location);
    std::cout << "\t\t\t\t\t\tLand Area (Acres): ";
    std::cin >> landArea;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tSoil Type: ";
    std::getline(std::cin, soilType);
    std::cout << "\t\t\t\t\t\tCrop Name: ";
    std::getline(std::cin, cropName);
    if(agricultureService.addFarm(farmerName, location, landArea, soilType, cropName))
        std::cout << "\n\t\t\t\t\t\tFarm Added Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tFailed To Add Farm.\n";
}

void FarmMenu::viewAllFarms()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Farm> farms;
    if (Core::AuthManager::isAdmin())
        farms = agricultureService.getAllFarms();
    else {
        Repositories::FarmRepository repo;
        farms = repo.getByTenant(currentTenant);
    }
    if(farms.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Farm Data Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t========================================================================================\n";
    std::cout << "\t\t\t\t\t\tID\tFarmer\t\tLocation\t\tArea\t\tSoil\t\tCrop\n";
    std::cout << "\t\t\t\t\t\t========================================================================================\n";
    for(const auto& farm : farms) {
        std::cout << "\t\t\t\t\t\t" << farm.getId() << "\t"
                  << farm.getFarmerName() << "\t\t"
                  << farm.getLocation() << "\t\t"
                  << farm.getLandArea() << "\t\t"
                  << farm.getSoilType() << "\t\t"
                  << farm.getCropName() << "\n";
    }
}

void FarmMenu::searchFarm()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tFarm ID: ";
    std::cin >> id;
    Entities::Farm farm;
    if(agricultureService.searchFarm(id, farm)) {
        std::cout << "\n\t\t\t\t\t\tID          : " << farm.getId();
        std::cout << "\n\t\t\t\t\t\tFarmer      : " << farm.getFarmerName();
        std::cout << "\n\t\t\t\t\t\tLocation    : " << farm.getLocation();
        std::cout << "\n\t\t\t\t\t\tLand Area   : " << farm.getLandArea();
        std::cout << "\n\t\t\t\t\t\tSoil Type   : " << farm.getSoilType();
        std::cout << "\n\t\t\t\t\t\tCrop Name   : " << farm.getCropName() << "\n";
    } else {
        std::cout << "\n\t\t\t\t\t\tFarm Not Found.\n";
    }
}

void FarmMenu::updateFarm()
{
    int id;
    std::string farmerName, location, soilType, cropName;
    double landArea;
    std::cout << "\n\t\t\t\t\t\tFarm ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tFarmer Name: ";
    std::getline(std::cin, farmerName);
    std::cout << "\t\t\t\t\t\tLocation: ";
    std::getline(std::cin, location);
    std::cout << "\t\t\t\t\t\tLand Area (Acres): ";
    std::cin >> landArea;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tSoil Type: ";
    std::getline(std::cin, soilType);
    std::cout << "\t\t\t\t\t\tCrop Name: ";
    std::getline(std::cin, cropName);
    if(agricultureService.updateFarm(id, farmerName, location, landArea, soilType, cropName))
        std::cout << "\n\t\t\t\t\t\tFarm Updated Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tUpdate Failed.\n";
}

void FarmMenu::deleteFarm()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tFarm ID: ";
    std::cin >> id;
    if(agricultureService.deleteFarm(id))
        std::cout << "\n\t\t\t\t\t\tFarm Deleted Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tDelete Failed.\n";
}

}
}