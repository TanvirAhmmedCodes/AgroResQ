#include "ReliefMenu.h"

#include <iostream>
#include <iomanip>

namespace AgroResQ
{
namespace UI
{

ReliefMenu::ReliefMenu() = default;

void ReliefMenu::show()
{
    int choice;

    do
    {
        std::cout
        << "\n=========================================\n";

        std::cout
        << "          RELIEF MANAGEMENT\n";

        std::cout
        << "=========================================\n";

        std::cout
        << "1. Add Relief Resource\n";

        std::cout
        << "2. View Relief Resources\n";

        std::cout
        << "3. Search Relief Resource\n";

        std::cout
        << "4. Update Relief Resource\n";

        std::cout
        << "5. Delete Relief Resource\n";

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
            addRelief();
            break;

        case 2:
            viewAllRelief();
            break;

        case 3:
            searchRelief();
            break;

        case 4:
            updateRelief();
            break;

        case 5:
            deleteRelief();
            break;

        case 0:
            break;

        default:
            std::cout
            << "\nInvalid Choice.\n";
        }

    }while(choice != 0);
}
void ReliefMenu::addRelief()
{
    std::string name;
    std::string category;
    std::string unit;
    int quantity;

    std::cin.ignore();

    std::cout << "\nResource Name: ";
    getline(std::cin, name);

    std::cout << "Category: ";
    getline(std::cin, category);

    std::cout << "Quantity: ";
    std::cin >> quantity;

    std::cin.ignore();

    std::cout << "Unit: ";
    getline(std::cin, unit);

    if(reliefService.addReliefResource(
        name,
        category,
        quantity,
        unit))
    {
        std::cout << "\nRelief Resource Added Successfully.\n";
    }
    else
    {
        std::cout << "\nFailed To Add Resource.\n";
    }
}
void ReliefMenu::viewAllRelief()
{
    auto resources =
        reliefService.getAllReliefResources();

    if(resources.empty())
    {
        std::cout << "\nNo Resource Found.\n";
        return;
    }

    std::cout
    << "\n====================================================================\n";

    std::cout
    << std::left
    << std::setw(5)  << "ID"
    << std::setw(20) << "Name"
    << std::setw(20) << "Category"
    << std::setw(12) << "Quantity"
    << std::setw(10) << "Unit"
    << "\n";

    std::cout
    << "====================================================================\n";

    for(auto& resource : resources)
    {
        std::cout
        << std::left
        << std::setw(5)  << resource.getId()
        << std::setw(20) << resource.getName()
        << std::setw(20) << resource.getCategory()
        << std::setw(12) << resource.getQuantity()
        << std::setw(10) << resource.getUnit()
        << "\n";
    }
}
void ReliefMenu::searchRelief()
{
    int id;

    std::cout << "\nResource ID: ";
    std::cin >> id;

    Entities::ReliefResource resource;

    if(reliefService.searchReliefResource(
        id,
        resource))
    {
        std::cout << "\nID        : " << resource.getId();
        std::cout << "\nName      : " << resource.getName();
        std::cout << "\nCategory  : " << resource.getCategory();
        std::cout << "\nQuantity  : " << resource.getQuantity();
        std::cout << "\nUnit      : " << resource.getUnit() << "\n";
    }
    else
    {
        std::cout << "\nResource Not Found.\n";
    }
}
void ReliefMenu::updateRelief()
{
    int id;
    int quantity;

    std::string name;
    std::string category;
    std::string unit;

    std::cout << "\nResource ID: ";
    std::cin >> id;

    std::cin.ignore();

    std::cout << "Name: ";
    getline(std::cin, name);

    std::cout << "Category: ";
    getline(std::cin, category);

    std::cout << "Quantity: ";
    std::cin >> quantity;

    std::cin.ignore();

    std::cout << "Unit: ";
    getline(std::cin, unit);

    if(reliefService.updateReliefResource(
        id,
        name,
        category,
        quantity,
        unit))
    {
        std::cout << "\nUpdated Successfully.\n";
    }
    else
    {
        std::cout << "\nUpdate Failed.\n";
    }
}
void ReliefMenu::deleteRelief()
{
    int id;

    std::cout << "\nResource ID: ";
    std::cin >> id;

    if(reliefService.deleteReliefResource(id))
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