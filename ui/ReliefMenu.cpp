#include "ReliefMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/disaster/ReliefRepository.h"
#include <iomanip>
#include <iostream>

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
        std::cout << "\n=========================================\n";
        std::cout << "          RELIEF MANAGEMENT\n";
        std::cout << "=========================================\n";
        std::cout << "1. Add Relief Resource\n";
        std::cout << "2. View Relief Resources\n";
        std::cout << "3. Search Relief Resource\n";
        std::cout << "4. Update Relief Resource\n";
        std::cout << "5. Delete Relief Resource\n";
        std::cout << "0. Back\n";
        std::cout << "=========================================\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
        case 1: addRelief(); break;
        case 2: viewAllRelief(); break;
        case 3: searchRelief(); break;
        case 4: updateRelief(); break;
        case 5: deleteRelief(); break;
        case 0: break;
        default: std::cout << "\nInvalid Choice.\n";
        }
    } while(choice != 0);
}

void ReliefMenu::addRelief()
{
    std::string name, category, unit;
    int quantity;
    std::cin.ignore();
    std::cout << "\n\t\t\t\t\t\tResource Name: ";
    std::getline(std::cin, name);
    std::cout << "\t\t\t\t\t\tCategory: ";
    std::getline(std::cin, category);
    std::cout << "\t\t\t\t\t\tQuantity: ";
    std::cin >> quantity;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tUnit: ";
    std::getline(std::cin, unit);
    if(reliefService.addReliefResource(name, category, quantity, unit))
        std::cout << "\n\t\t\t\t\t\tRelief Resource Added Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tFailed To Add Resource.\n";
}

void ReliefMenu::viewAllRelief()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::ReliefResource> resources;
    if (Core::AuthManager::isAdmin())
        resources = reliefService.getAllReliefResources();
    else {
        Repositories::ReliefRepository repo;
        resources = repo.getByTenant(currentTenant);
    }
    if(resources.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Resource Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t====================================================================\n";
    std::cout << "\t\t\t\t\t\tID\tName\t\t\tCategory\t\tQuantity\tUnit\n";
    std::cout << "\t\t\t\t\t\t====================================================================\n";
    for(auto& r : resources) {
        std::cout << "\t\t\t\t\t\t" << r.getId() << "\t"
                  << r.getName() << "\t\t\t"
                  << r.getCategory() << "\t\t"
                  << r.getQuantity() << "\t\t"
                  << r.getUnit() << "\n";
    }
}

void ReliefMenu::searchRelief()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tResource ID: ";
    std::cin >> id;
    Entities::ReliefResource resource;
    if(reliefService.searchReliefResource(id, resource)) {
        std::cout << "\n\t\t\t\t\t\tID        : " << resource.getId();
        std::cout << "\n\t\t\t\t\t\tName      : " << resource.getName();
        std::cout << "\n\t\t\t\t\t\tCategory  : " << resource.getCategory();
        std::cout << "\n\t\t\t\t\t\tQuantity  : " << resource.getQuantity();
        std::cout << "\n\t\t\t\t\t\tUnit      : " << resource.getUnit() << "\n";
    } else {
        std::cout << "\n\t\t\t\t\t\tResource Not Found.\n";
    }
}

void ReliefMenu::updateRelief()
{
    int id, quantity;
    std::string name, category, unit;
    std::cout << "\n\t\t\t\t\t\tResource ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tName: ";
    std::getline(std::cin, name);
    std::cout << "\t\t\t\t\t\tCategory: ";
    std::getline(std::cin, category);
    std::cout << "\t\t\t\t\t\tQuantity: ";
    std::cin >> quantity;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tUnit: ";
    std::getline(std::cin, unit);
    if(reliefService.updateReliefResource(id, name, category, quantity, unit))
        std::cout << "\n\t\t\t\t\t\tUpdated Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tUpdate Failed.\n";
}

void ReliefMenu::deleteRelief()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tResource ID: ";
    std::cin >> id;
    if(reliefService.deleteReliefResource(id))
        std::cout << "\n\t\t\t\t\t\tDeleted Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tDelete Failed.\n";
}

}
}