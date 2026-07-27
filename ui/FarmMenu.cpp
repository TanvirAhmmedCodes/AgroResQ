#include "FarmMenu.h"

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
        case 1:
            addFarm();
            break;

        case 2:
            viewAllFarms();
            break;

        case 3:
            searchFarm();
            break;

        case 4:
            updateFarm();
            break;

        case 5:
            deleteFarm();
            break;

        case 0:
            break;

        default:
            std::cout << "\nInvalid Choice.\n";
        }

    } while (choice != 0);
}

void FarmMenu::addFarm()
{
    std::string farmerName;
    std::string location;
    std::string soilType;
    std::string cropName;

    double landArea;

    std::cin.ignore();

    std::cout << "\nFarmer Name: ";
    std::getline(std::cin, farmerName);

    std::cout << "Location: ";
    std::getline(std::cin, location);

    std::cout << "Land Area (Acres): ";
    std::cin >> landArea;

    std::cin.ignore();

    std::cout << "Soil Type: ";
    std::getline(std::cin, soilType);

    std::cout << "Crop Name: ";
    std::getline(std::cin, cropName);

    if (agricultureService.addFarm(
            farmerName,
            location,
            landArea,
            soilType,
            cropName))
    {
        std::cout << "\nFarm Added Successfully.\n";
    }
    else
    {
        std::cout << "\nFailed To Add Farm.\n";
    }
}
void FarmMenu::viewAllFarms()
{
    std::vector<Entities::Farm> farms =
        agricultureService.getAllFarms();

    if(farms.empty())
    {
        std::cout << "\nNo Farm Data Found.\n";
        return;
    }

    std::cout << "\n========================================================================================\n";

    std::cout
        << std::left
        << std::setw(5)  << "ID"
        << std::setw(20) << "Farmer"
        << std::setw(20) << "Location"
        << std::setw(12) << "Area"
        << std::setw(18) << "Soil"
        << std::setw(18) << "Crop"
        << "\n";

    std::cout << "========================================================================================\n";

    for(const auto& farm : farms)
    {
        std::cout
            << std::left
            << std::setw(5)  << farm.getId()
            << std::setw(20) << farm.getFarmerName()
            << std::setw(20) << farm.getLocation()
            << std::setw(12) << farm.getLandArea()
            << std::setw(18) << farm.getSoilType()
            << std::setw(18) << farm.getCropName()
            << "\n";
    }
}


void FarmMenu::searchFarm()
{
    int id;

    std::cout << "\nFarm ID: ";
    std::cin >> id;

    Entities::Farm farm;

    if(agricultureService.searchFarm(id, farm))
    {
        std::cout << "\nID          : " << farm.getId();
        std::cout << "\nFarmer      : " << farm.getFarmerName();
        std::cout << "\nLocation    : " << farm.getLocation();
        std::cout << "\nLand Area   : " << farm.getLandArea();
        std::cout << "\nSoil Type   : " << farm.getSoilType();
        std::cout << "\nCrop Name   : " << farm.getCropName()
                  << "\n";
    }
    else
    {
        std::cout << "\nFarm Not Found.\n";
    }
}
void FarmMenu::updateFarm()
{
    int id;

    std::string farmerName;
    std::string location;
    std::string soilType;
    std::string cropName;

    double landArea;

    std::cout << "\nFarm ID: ";
    std::cin >> id;

    std::cin.ignore();

    std::cout << "Farmer Name: ";
    std::getline(std::cin, farmerName);

    std::cout << "Location: ";
    std::getline(std::cin, location);

    std::cout << "Land Area (Acres): ";
    std::cin >> landArea;

    std::cin.ignore();

    std::cout << "Soil Type: ";
    std::getline(std::cin, soilType);

    std::cout << "Crop Name: ";
    std::getline(std::cin, cropName);

    if(agricultureService.updateFarm(
        id,
        farmerName,
        location,
        landArea,
        soilType,
        cropName))
    {
        std::cout << "\nFarm Updated Successfully.\n";
    }
    else
    {
        std::cout << "\nUpdate Failed.\n";
    }
}


void FarmMenu::deleteFarm()
{
    int id;

    std::cout << "\nFarm ID: ";
    std::cin >> id;

    if(agricultureService.deleteFarm(id))
    {
        std::cout << "\nFarm Deleted Successfully.\n";
    }
    else
    {
        std::cout << "\nDelete Failed.\n";
    }
}

}
}