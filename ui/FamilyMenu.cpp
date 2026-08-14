#include "FamilyMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/victim/FamilyRepository.h"
#include <iomanip>
#include <iostream>

namespace AgroResQ
{
namespace UI
{

FamilyMenu::FamilyMenu() = default;

void FamilyMenu::show()
{
    int choice;
    do
    {
        std::cout << "\n=========================================\n";
        std::cout << "          FAMILY MANAGEMENT\n";
        std::cout << "=========================================\n";
        std::cout << "1. Add Family\n";
        std::cout << "2. View Families\n";
        std::cout << "3. Search Family\n";
        std::cout << "4. Update Family\n";
        std::cout << "5. Delete Family\n";
        std::cout << "6. Displaced Families\n";
        std::cout << "0. Back\n";
        std::cout << "=========================================\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
        case 1: addFamily(); break;
        case 2: viewAllFamilies(); break;
        case 3: searchFamily(); break;
        case 4: updateFamily(); break;
        case 5: deleteFamily(); break;
        case 6: viewDisplacedFamilies(); break;
        case 0: break;
        default: std::cout << "\nInvalid Choice.\n";
        }
    } while(choice != 0);
}

void FamilyMenu::addFamily()
{
    std::string headName, address, contact;
    int memberCount;
    char displacedInput;
    bool displaced;
    std::cin.ignore();
    std::cout << "\n\t\t\t\t\t\tHead Name: ";
    std::getline(std::cin, headName);
    std::cout << "\t\t\t\t\t\tAddress: ";
    std::getline(std::cin, address);
    std::cout << "\t\t\t\t\t\tContact: ";
    std::getline(std::cin, contact);
    std::cout << "\t\t\t\t\t\tMember Count: ";
    std::cin >> memberCount;
    std::cout << "\t\t\t\t\t\tDisplaced? (y/n): ";
    std::cin >> displacedInput;
    displaced = (displacedInput == 'y' || displacedInput == 'Y');
    if(familyService.addFamily(headName, address, contact, memberCount, displaced))
        std::cout << "\n\t\t\t\t\t\tFamily Added Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tFailed To Add Family.\n";
}

void FamilyMenu::viewAllFamilies()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Family> families;
    if (Core::AuthManager::isAdmin())
        families = familyService.getAllFamilies();
    else {
        Repositories::FamilyRepository repo;
        families = repo.getByTenant(currentTenant);
    }
    if(families.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Families Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t============================================================================\n";
    std::cout << "\t\t\t\t\t\tID\tHead Name\t\tAddress\t\t\tMembers\tStatus\n";
    std::cout << "\t\t\t\t\t\t============================================================================\n";
    for(std::size_t i = 0; i < families.size(); ++i) {
        std::cout << "\t\t\t\t\t\t" << families[i].getId() << "\t"
                  << families[i].getHeadName() << "\t\t"
                  << families[i].getAddress() << "\t\t"
                  << families[i].getMemberCount() << "\t"
                  << (families[i].isDisplaced() ? "Displaced" : "Safe") << "\n";
    }
}

void FamilyMenu::searchFamily()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tFamily ID: ";
    std::cin >> id;
    Entities::Family family;
    if(familyService.searchFamily(id, family)) {
        std::cout << "\n\t\t\t\t\t\tID          : " << family.getId();
        std::cout << "\n\t\t\t\t\t\tHead Name   : " << family.getHeadName();
        std::cout << "\n\t\t\t\t\t\tAddress     : " << family.getAddress();
        std::cout << "\n\t\t\t\t\t\tContact     : " << family.getContact();
        std::cout << "\n\t\t\t\t\t\tMembers     : " << family.getMemberCount();
        std::cout << "\n\t\t\t\t\t\tStatus      : " << (family.isDisplaced() ? "Displaced" : "Safe") << "\n";
    } else {
        std::cout << "\n\t\t\t\t\t\tFamily Not Found.\n";
    }
}

void FamilyMenu::updateFamily()
{
    int id, memberCount;
    std::string headName, address, contact;
    char displacedInput;
    bool displaced;
    std::cout << "\n\t\t\t\t\t\tFamily ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tHead Name: ";
    std::getline(std::cin, headName);
    std::cout << "\t\t\t\t\t\tAddress: ";
    std::getline(std::cin, address);
    std::cout << "\t\t\t\t\t\tContact: ";
    std::getline(std::cin, contact);
    std::cout << "\t\t\t\t\t\tMember Count: ";
    std::cin >> memberCount;
    std::cout << "\t\t\t\t\t\tDisplaced? (y/n): ";
    std::cin >> displacedInput;
    displaced = (displacedInput == 'y' || displacedInput == 'Y');
    if(familyService.updateFamily(id, headName, address, contact, memberCount, displaced))
        std::cout << "\n\t\t\t\t\t\tUpdated Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tUpdate Failed.\n";
}

void FamilyMenu::deleteFamily()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tFamily ID: ";
    std::cin >> id;
    if(familyService.deleteFamily(id))
        std::cout << "\n\t\t\t\t\t\tDeleted Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tDelete Failed.\n";
}

void FamilyMenu::viewDisplacedFamilies()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Family> families;
    if (Core::AuthManager::isAdmin())
        families = familyService.getDisplacedFamilies();
    else {
        Repositories::FamilyRepository repo;
        auto all = repo.getByTenant(currentTenant);
        for(auto& f : all) {
            if(f.isDisplaced()) families.push_back(f);
        }
    }
    if(families.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Displaced Families.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\tDisplaced Families:\n";
    for(std::size_t i = 0; i < families.size(); ++i) {
        std::cout << "\t\t\t\t\t\tID: " << families[i].getId()
                  << " | Head: " << families[i].getHeadName()
                  << " | Members: " << families[i].getMemberCount()
                  << " | Address: " << families[i].getAddress() << "\n";
    }
}

}
}