#include "CropMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/agriculture/CropRepository.h"
#include <iomanip>
#include <iostream>

namespace AgroResQ
{
namespace UI
{

CropMenu::CropMenu() = default;

void CropMenu::show()
{
    int choice;
    do
    {
        std::cout << "\n=========================================\n";
        std::cout << "             CROP MANAGEMENT\n";
        std::cout << "=========================================\n";
        std::cout << "1. Add Crop\n";
        std::cout << "2. View Crops\n";
        std::cout << "3. Search Crop\n";
        std::cout << "4. Update Crop\n";
        std::cout << "5. Delete Crop\n";
        std::cout << "0. Back\n";
        std::cout << "=========================================\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
        case 1: addCrop(); break;
        case 2: viewAllCrops(); break;
        case 3: searchCrop(); break;
        case 4: updateCrop(); break;
        case 5: deleteCrop(); break;
        case 0: break;
        default: std::cout << "\nInvalid Choice.\n";
        }
    } while(choice != 0);
}

void CropMenu::addCrop()
{
    std::string cropName, season, suitableSoil;
    double waterRequirement;
    std::cin.ignore();
    std::cout << "\n\t\t\t\t\t\tCrop Name: ";
    std::getline(std::cin, cropName);
    std::cout << "\t\t\t\t\t\tSeason: ";
    std::getline(std::cin, season);
    std::cout << "\t\t\t\t\t\tSuitable Soil: ";
    std::getline(std::cin, suitableSoil);
    std::cout << "\t\t\t\t\t\tWater Requirement: ";
    std::cin >> waterRequirement;
    if(cropService.addCrop(cropName, season, suitableSoil, waterRequirement))
        std::cout << "\n\t\t\t\t\t\tCrop Added Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tFailed To Add Crop.\n";
}

void CropMenu::viewAllCrops()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Crop> crops;
    if (Core::AuthManager::isAdmin())
        crops = cropService.getAllCrops();
    else {
        Repositories::CropRepository repo;
        crops = repo.getByTenant(currentTenant);
    }
    if(crops.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Crop Data Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t====================================================================\n";
    std::cout << "\t\t\t\t\t\tID\tCrop\t\tSeason\t\tSoil\t\tWater\n";
    std::cout << "\t\t\t\t\t\t====================================================================\n";
    for(const auto& crop : crops) {
        std::cout << "\t\t\t\t\t\t" << crop.getId() << "\t"
                  << crop.getCropName() << "\t\t"
                  << crop.getSeason() << "\t\t"
                  << crop.getSuitableSoil() << "\t\t"
                  << crop.getWaterRequirement() << "\n";
    }
}

void CropMenu::searchCrop()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tCrop ID: ";
    std::cin >> id;
    Entities::Crop crop;
    if(cropService.searchCrop(id, crop)) {
        std::cout << "\n\t\t\t\t\t\tID                : " << crop.getId();
        std::cout << "\n\t\t\t\t\t\tCrop Name         : " << crop.getCropName();
        std::cout << "\n\t\t\t\t\t\tSeason            : " << crop.getSeason();
        std::cout << "\n\t\t\t\t\t\tSuitable Soil     : " << crop.getSuitableSoil();
        std::cout << "\n\t\t\t\t\t\tWater Requirement : " << crop.getWaterRequirement() << "\n";
    } else {
        std::cout << "\n\t\t\t\t\t\tCrop Not Found.\n";
    }
}

void CropMenu::updateCrop()
{
    int id;
    std::string cropName, season, suitableSoil;
    double waterRequirement;
    std::cout << "\n\t\t\t\t\t\tCrop ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tCrop Name: ";
    std::getline(std::cin, cropName);
    std::cout << "\t\t\t\t\t\tSeason: ";
    std::getline(std::cin, season);
    std::cout << "\t\t\t\t\t\tSuitable Soil: ";
    std::getline(std::cin, suitableSoil);
    std::cout << "\t\t\t\t\t\tWater Requirement: ";
    std::cin >> waterRequirement;
    if(cropService.updateCrop(id, cropName, season, suitableSoil, waterRequirement))
        std::cout << "\n\t\t\t\t\t\tUpdated Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tUpdate Failed.\n";
}

void CropMenu::deleteCrop()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tCrop ID: ";
    std::cin >> id;
    if(cropService.deleteCrop(id))
        std::cout << "\n\t\t\t\t\t\tDeleted Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tDelete Failed.\n";
}

}
}