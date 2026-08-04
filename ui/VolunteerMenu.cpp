#include "VolunteerMenu.h"
#include <iostream>
#include <iomanip>

namespace AgroResQ
{
    namespace UI
    {
        VolunteerMenu::VolunteerMenu() = default;

        void VolunteerMenu::show()
        {
            int choice;
            do
            {
                std::cout << "\n=========================================\n";
                std::cout << "         VOLUNTEER MANAGEMENT\n";
                std::cout << "=========================================\n";
                std::cout << "1. Add Volunteer\n";
                std::cout << "2. View Volunteers\n";
                std::cout << "3. Search Volunteer\n";
                std::cout << "4. Update Volunteer\n";
                std::cout << "5. Delete Volunteer\n";
                std::cout << "6. Available Volunteers\n";
                std::cout << "7. Assign Task\n";
                std::cout << "0. Back\n";
                std::cout << "=========================================\n";
                std::cout << "Enter Choice: ";
                std::cin >> choice;

                switch (choice)
                {
                case 1:
                    addVolunteer();
                    break;
                case 2:
                    viewAllVolunteers();
                    break;
                case 3:
                    searchVolunteer();
                    break;
                case 4:
                    updateVolunteer();
                    break;
                case 5:
                    deleteVolunteer();
                    break;
                case 6:
                    viewAvailableVolunteers();
                    break;
                case 7:
                    assignTask();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "\nInvalid Choice.\n";
                }
            } while (choice != 0);
        }

        void VolunteerMenu::addVolunteer()
        {
            std::string name, skill, location, contact;
            char availableInput;
            bool available;

            std::cin.ignore();
            std::cout << "\nName: ";
            getline(std::cin, name);
            std::cout << "Skill (e.g., Medical, Rescue, Logistics): ";
            getline(std::cin, skill);
            std::cout << "Location: ";
            getline(std::cin, location);
            std::cout << "Contact: ";
            getline(std::cin, contact);
            std::cout << "Available (y/n): ";
            std::cin >> availableInput;

            available = (availableInput == 'y' || availableInput == 'Y');

            if (volunteerService.addVolunteer(name, skill, location, contact, available))
            {
                std::cout << "\nVolunteer Added Successfully.\n";
            }
            else
            {
                std::cout << "\nFailed To Add Volunteer.\n";
            }
        }

        void VolunteerMenu::viewAllVolunteers()
        {
            auto volunteers = volunteerService.getAllVolunteers();
            if (volunteers.empty())
            {
                std::cout << "\nNo Volunteers Found.\n";
                return;
            }

            std::cout << "\n====================================================================\n";
            std::cout << std::left
                << std::setw(5) << "ID"
                << std::setw(20) << "Name"
                << std::setw(15) << "Skill"
                << std::setw(15) << "Location"
                << std::setw(12) << "Status"
                << "\n";
            std::cout << "====================================================================\n";

            for (auto& v : volunteers)
            {
                std::cout << std::left
                    << std::setw(5) << v.getId()
                    << std::setw(20) << v.getName()
                    << std::setw(15) << v.getSkill()
                    << std::setw(15) << v.getLocation()
                    << std::setw(12) << (v.isAvailable() ? "Available" : "Busy")
                    << "\n";
            }
        }

        void VolunteerMenu::searchVolunteer()
        {
            int id;
            std::cout << "\nVolunteer ID: ";
            std::cin >> id;

            Entities::Volunteer volunteer;
            if (volunteerService.searchVolunteer(id, volunteer))
            {
                std::cout << "\nID       : " << volunteer.getId();
                std::cout << "\nName     : " << volunteer.getName();
                std::cout << "\nSkill    : " << volunteer.getSkill();
                std::cout << "\nLocation : " << volunteer.getLocation();
                std::cout << "\nContact  : " << volunteer.getContact();
                std::cout << "\nStatus   : " << (volunteer.isAvailable() ? "Available" : "Busy") << "\n";
            }
            else
            {
                std::cout << "\nVolunteer Not Found.\n";
            }
        }

        void VolunteerMenu::updateVolunteer()
        {
            int id;
            std::string name, skill, location, contact;
            char availableInput;
            bool available;

            std::cout << "\nVolunteer ID: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Name: ";
            getline(std::cin, name);
            std::cout << "Skill: ";
            getline(std::cin, skill);
            std::cout << "Location: ";
            getline(std::cin, location);
            std::cout << "Contact: ";
            getline(std::cin, contact);
            std::cout << "Available (y/n): ";
            std::cin >> availableInput;

            available = (availableInput == 'y' || availableInput == 'Y');

            if (volunteerService.updateVolunteer(id, name, skill, location, contact, available))
            {
                std::cout << "\nUpdated Successfully.\n";
            }
            else
            {
                std::cout << "\nUpdate Failed.\n";
            }
        }

        void VolunteerMenu::deleteVolunteer()
        {
            int id;
            std::cout << "\nVolunteer ID: ";
            std::cin >> id;

            if (volunteerService.deleteVolunteer(id))
            {
                std::cout << "\nDeleted Successfully.\n";
            }
            else
            {
                std::cout << "\nDelete Failed.\n";
            }
        }

        void VolunteerMenu::viewAvailableVolunteers()
        {
            auto volunteers = volunteerService.getAvailableVolunteers();
            if (volunteers.empty())
            {
                std::cout << "\nNo Available Volunteers.\n";
                return;
            }

            std::cout << "\nAvailable Volunteers:\n";
            for (auto& v : volunteers)
            {
                std::cout << "ID: " << v.getId()
                    << " | Name: " << v.getName()
                    << " | Skill: " << v.getSkill()
                    << " | Location: " << v.getLocation() << "\n";
            }
        }

        void VolunteerMenu::assignTask()
        {
            int id;
            std::string task;

            viewAvailableVolunteers();

            std::cout << "\nEnter Volunteer ID: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Enter Task Description: ";
            getline(std::cin, task);

            if (volunteerService.assignTask(id, task))
            {
                std::cout << "\nTask Assigned Successfully.\n";
            }
            else
            {
                std::cout << "\nTask Assignment Failed.\n";
            }
        }
    }
}