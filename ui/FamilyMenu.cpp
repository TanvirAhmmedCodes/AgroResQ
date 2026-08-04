#include "FamilyMenu.h"
#include <iostream>
#include <iomanip>

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

                switch (choice)
                {
                case 1:
                    addFamily();
                    break;
                case 2:
                    viewAllFamilies();
                    break;
                case 3:
                    searchFamily();
                    break;
                case 4:
                    updateFamily();
                    break;
                case 5:
                    deleteFamily();
                    break;
                case 6:
                    viewDisplacedFamilies();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "\nInvalid Choice.\n";
                }
            } while (choice != 0);
        }

        void FamilyMenu::addFamily()
        {
            std::string headName, address, contact;
            int memberCount;
            char displacedInput;
            bool displaced;

            std::cin.ignore();
            std::cout << "\nHead Name: ";
            getline(std::cin, headName);
            std::cout << "Address: ";
            getline(std::cin, address);
            std::cout << "Contact: ";
            getline(std::cin, contact);
            std::cout << "Member Count: ";
            std::cin >> memberCount;
            std::cout << "Displaced? (y/n): ";
            std::cin >> displacedInput;

            displaced = (displacedInput == 'y' || displacedInput == 'Y');

            if (familyService.addFamily(headName, address, contact, memberCount, displaced))
            {
                std::cout << "\nFamily Added Successfully.\n";
            }
            else
            {
                std::cout << "\nFailed To Add Family.\n";
            }
        }

        void FamilyMenu::viewAllFamilies()
        {
            std::vector<Entities::Family> families = familyService.getAllFamilies();

            if (families.empty())
            {
                std::cout << "\nNo Families Found.\n";
                return;
            }

            std::cout << "\n============================================================================\n";
            std::cout << std::left
                << std::setw(5) << "ID"
                << std::setw(20) << "Head Name"
                << std::setw(20) << "Address"
                << std::setw(12) << "Members"
                << std::setw(12) << "Status"
                << "\n";
            std::cout << "============================================================================\n";

            for (std::size_t i = 0; i < families.size(); ++i)
            {
                std::cout << std::left
                    << std::setw(5) << families[i].getId()
                    << std::setw(20) << families[i].getHeadName()
                    << std::setw(20) << families[i].getAddress()
                    << std::setw(12) << families[i].getMemberCount()
                    << std::setw(12) << (families[i].isDisplaced() ? "Displaced" : "Safe")
                    << "\n";
            }
        }

        void FamilyMenu::searchFamily()
        {
            int id;
            std::cout << "\nFamily ID: ";
            std::cin >> id;

            Entities::Family family;
            if (familyService.searchFamily(id, family))
            {
                std::cout << "\nID          : " << family.getId();
                std::cout << "\nHead Name   : " << family.getHeadName();
                std::cout << "\nAddress     : " << family.getAddress();
                std::cout << "\nContact     : " << family.getContact();
                std::cout << "\nMembers     : " << family.getMemberCount();
                std::cout << "\nStatus      : " << (family.isDisplaced() ? "Displaced" : "Safe") << "\n";
            }
            else
            {
                std::cout << "\nFamily Not Found.\n";
            }
        }

        void FamilyMenu::updateFamily()
        {
            int id, memberCount;
            std::string headName, address, contact;
            char displacedInput;
            bool displaced;

            std::cout << "\nFamily ID: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Head Name: ";
            getline(std::cin, headName);
            std::cout << "Address: ";
            getline(std::cin, address);
            std::cout << "Contact: ";
            getline(std::cin, contact);
            std::cout << "Member Count: ";
            std::cin >> memberCount;
            std::cout << "Displaced? (y/n): ";
            std::cin >> displacedInput;

            displaced = (displacedInput == 'y' || displacedInput == 'Y');

            if (familyService.updateFamily(id, headName, address, contact, memberCount, displaced))
            {
                std::cout << "\nUpdated Successfully.\n";
            }
            else
            {
                std::cout << "\nUpdate Failed.\n";
            }
        }

        void FamilyMenu::deleteFamily()
        {
            int id;
            std::cout << "\nFamily ID: ";
            std::cin >> id;

            if (familyService.deleteFamily(id))
            {
                std::cout << "\nDeleted Successfully.\n";
            }
            else
            {
                std::cout << "\nDelete Failed.\n";
            }
        }

        void FamilyMenu::viewDisplacedFamilies()
        {
            std::vector<Entities::Family> families = familyService.getDisplacedFamilies();

            if (families.empty())
            {
                std::cout << "\nNo Displaced Families.\n";
                return;
            }

            std::cout << "\nDisplaced Families:\n";
            for (std::size_t i = 0; i < families.size(); ++i)
            {
                std::cout << "ID: " << families[i].getId()
                    << " | Head: " << families[i].getHeadName()
                    << " | Members: " << families[i].getMemberCount()
                    << " | Address: " << families[i].getAddress() << "\n";
            }
        }
    }
}