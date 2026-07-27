#include "SoilMenu.h"

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
        case 1:
            addSoil();
            break;

        case 2:
            viewAllSoils();
            break;

        case 3:
            searchSoil();
            break;

        case 4:
            updateSoil();
            break;

        case 5:
            deleteSoil();
            break;

        case 0:
            break;

        default:
            std::cout << "\nInvalid Choice.\n";
        }

    } while(choice != 0);
}


void SoilMenu::addSoil()
{
    std::string farmId;
    std::string soilType;

    double phLevel;
    double moisture;


    std::cout << "\nFarm ID: ";
    std::cin >> farmId;

    std::cout << "PH Level (0-14): ";
    std::cin >> phLevel;

    std::cout << "Moisture Percentage: ";
    std::cin >> moisture;

    std::cin.ignore();

    std::cout << "Soil Type: ";
    std::getline(std::cin, soilType);


    if(soilService.addSoil(
        farmId,
        phLevel,
        moisture,
        soilType))
    {
        std::cout << "\nSoil Data Added Successfully.\n";
    }
    else
    {
        std::cout << "\nFailed To Add Soil Data.\n";
    }
}


void SoilMenu::viewAllSoils()
{
    std::vector<Entities::Soil> soils =
        soilService.getAllSoils();


    if(soils.empty())
    {
        std::cout << "\nNo Soil Data Found.\n";
        return;
    }


    std::cout << "\n============================================================\n";

    std::cout
        << std::left
        << std::setw(5) << "ID"
        << std::setw(12) << "Farm"
        << std::setw(12) << "PH"
        << std::setw(12) << "Moisture"
        << std::setw(20) << "Type"
        << "\n";


    std::cout << "============================================================\n";


    for(const auto& soil : soils)
    {
        std::cout
            << std::left
            << std::setw(5) << soil.getId()
            << std::setw(12) << soil.getFarmId()
            << std::setw(12) << soil.getPhLevel()
            << std::setw(12) << soil.getMoisture()
            << std::setw(20) << soil.getSoilType()
            << "\n";
    }
}


void SoilMenu::searchSoil()
{
    int id;

    std::cout << "\nEnter Soil ID: ";
    std::cin >> id;


    Entities::Soil soil;


    if(soilService.searchSoil(id, soil))
    {
        std::cout << "\nID        : " << soil.getId();
        std::cout << "\nFarm ID   : " << soil.getFarmId();
        std::cout << "\nPH Level  : " << soil.getPhLevel();
        std::cout << "\nMoisture  : " << soil.getMoisture();
        std::cout << "\nSoil Type : " << soil.getSoilType() << "\n";
    }
    else
    {
        std::cout << "\nSoil Data Not Found.\n";
    }
}


void SoilMenu::updateSoil()
{
    int id;

    std::string farmId;
    std::string soilType;

    double phLevel;
    double moisture;


    std::cout << "\nSoil ID: ";
    std::cin >> id;


    std::cout << "Farm ID: ";
    std::cin >> farmId;

    std::cout << "PH Level: ";
    std::cin >> phLevel;

    std::cout << "Moisture: ";
    std::cin >> moisture;

    std::cin.ignore();

    std::cout << "Soil Type: ";
    std::getline(std::cin, soilType);



    if(soilService.updateSoil(
        id,
        farmId,
        phLevel,
        moisture,
        soilType))
    {
        std::cout << "\nUpdated Successfully.\n";
    }
    else
    {
        std::cout << "\nUpdate Failed.\n";
    }
}


void SoilMenu::deleteSoil()
{
    int id;

    std::cout << "\nSoil ID: ";
    std::cin >> id;


    if(soilService.deleteSoil(id))
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