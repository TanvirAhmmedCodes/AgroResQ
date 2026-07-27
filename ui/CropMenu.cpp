#include "CropMenu.h"

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
        case 1:
            addCrop();
            break;

        case 2:
            viewAllCrops();
            break;

        case 3:
            searchCrop();
            break;

        case 4:
            updateCrop();
            break;

        case 5:
            deleteCrop();
            break;

        case 0:
            break;

        default:
            std::cout << "\nInvalid Choice.\n";
        }

    } while(choice != 0);
}


void CropMenu::addCrop()
{
    std::string cropName;
    std::string season;
    std::string suitableSoil;

    double waterRequirement;


    std::cin.ignore();

    std::cout << "\nCrop Name: ";
    std::getline(std::cin, cropName);

    std::cout << "Season: ";
    std::getline(std::cin, season);

    std::cout << "Suitable Soil: ";
    std::getline(std::cin, suitableSoil);

    std::cout << "Water Requirement: ";
    std::cin >> waterRequirement;


    if(cropService.addCrop(
        cropName,
        season,
        suitableSoil,
        waterRequirement))
    {
        std::cout << "\nCrop Added Successfully.\n";
    }
    else
    {
        std::cout << "\nFailed To Add Crop.\n";
    }
}


void CropMenu::viewAllCrops()
{
    std::vector<Entities::Crop> crops =
        cropService.getAllCrops();


    if(crops.empty())
    {
        std::cout << "\nNo Crop Data Found.\n";
        return;
    }


    std::cout << "\n====================================================================\n";

    std::cout
        << std::left
        << std::setw(5) << "ID"
        << std::setw(20) << "Crop"
        << std::setw(15) << "Season"
        << std::setw(20) << "Soil"
        << std::setw(15) << "Water"
        << "\n";


    std::cout << "====================================================================\n";


    for(const auto& crop : crops)
    {
        std::cout
            << std::left
            << std::setw(5) << crop.getId()
            << std::setw(20) << crop.getCropName()
            << std::setw(15) << crop.getSeason()
            << std::setw(20) << crop.getSuitableSoil()
            << std::setw(15) << crop.getWaterRequirement()
            << "\n";
    }
}


void CropMenu::searchCrop()
{
    int id;

    std::cout << "\nCrop ID: ";
    std::cin >> id;


    Entities::Crop crop;


    if(cropService.searchCrop(id, crop))
    {
        std::cout << "\nID                : " << crop.getId();
        std::cout << "\nCrop Name         : " << crop.getCropName();
        std::cout << "\nSeason            : " << crop.getSeason();
        std::cout << "\nSuitable Soil     : " << crop.getSuitableSoil();
        std::cout << "\nWater Requirement : " << crop.getWaterRequirement()
                  << "\n";
    }
    else
    {
        std::cout << "\nCrop Not Found.\n";
    }
}


void CropMenu::updateCrop()
{
    int id;

    std::string cropName;
    std::string season;
    std::string suitableSoil;

    double waterRequirement;


    std::cout << "\nCrop ID: ";
    std::cin >> id;

    std::cin.ignore();


    std::cout << "Crop Name: ";
    std::getline(std::cin, cropName);

    std::cout << "Season: ";
    std::getline(std::cin, season);

    std::cout << "Suitable Soil: ";
    std::getline(std::cin, suitableSoil);

    std::cout << "Water Requirement: ";
    std::cin >> waterRequirement;


    if(cropService.updateCrop(
        id,
        cropName,
        season,
        suitableSoil,
        waterRequirement))
    {
        std::cout << "\nUpdated Successfully.\n";
    }
    else
    {
        std::cout << "\nUpdate Failed.\n";
    }
}


void CropMenu::deleteCrop()
{
    int id;

    std::cout << "\nCrop ID: ";
    std::cin >> id;


    if(cropService.deleteCrop(id))
    {
        std::cout << "\nDeleted Successfully.\n";
    }
    else
    {
        std::cout << "\nDelete Failed.\n";
    }
}

}
}