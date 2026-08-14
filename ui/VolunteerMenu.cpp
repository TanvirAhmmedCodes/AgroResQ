#include "VolunteerMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/disaster/VolunteerRepository.h"
#include <iomanip>
#include <iostream>

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

        switch(choice)
        {
        case 1: addVolunteer(); break;
        case 2: viewAllVolunteers(); break;
        case 3: searchVolunteer(); break;
        case 4: updateVolunteer(); break;
        case 5: deleteVolunteer(); break;
        case 6: viewAvailableVolunteers(); break;
        case 7: assignTask(); break;
        case 0: break;
        default: std::cout << "\nInvalid Choice.\n";
        }
    } while(choice != 0);
}

void VolunteerMenu::addVolunteer()
{
    std::string name, skill, location, contact;
    char availableInput;
    bool available;
    std::cin.ignore();
    std::cout << "\n\t\t\t\t\t\tName: ";
    std::getline(std::cin, name);
    std::cout << "\t\t\t\t\t\tSkill (e.g., Medical, Rescue, Logistics): ";
    std::getline(std::cin, skill);
    std::cout << "\t\t\t\t\t\tLocation: ";
    std::getline(std::cin, location);
    std::cout << "\t\t\t\t\t\tContact: ";
    std::getline(std::cin, contact);
    std::cout << "\t\t\t\t\t\tAvailable (y/n): ";
    std::cin >> availableInput;
    available = (availableInput == 'y' || availableInput == 'Y');
    if(volunteerService.addVolunteer(name, skill, location, contact, available))
        std::cout << "\n\t\t\t\t\t\tVolunteer Added Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tFailed To Add Volunteer.\n";
}

void VolunteerMenu::viewAllVolunteers()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Volunteer> volunteers;
    if (Core::AuthManager::isAdmin())
        volunteers = volunteerService.getAllVolunteers();
    else {
        Repositories::VolunteerRepository repo;
        volunteers = repo.getByTenant(currentTenant);
    }
    if(volunteers.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Volunteers Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t====================================================================\n";
    std::cout << "\t\t\t\t\t\tID\tName\t\t\tSkill\t\t\tLocation\tStatus\n";
    std::cout << "\t\t\t\t\t\t====================================================================\n";
    for(auto& v : volunteers) {
        std::cout << "\t\t\t\t\t\t" << v.getId() << "\t"
                  << v.getName() << "\t\t\t"
                  << v.getSkill() << "\t\t\t"
                  << v.getLocation() << "\t\t"
                  << (v.isAvailable() ? "Available" : "Busy") << "\n";
    }
}

void VolunteerMenu::searchVolunteer()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tVolunteer ID: ";
    std::cin >> id;
    Entities::Volunteer volunteer;
    if(volunteerService.searchVolunteer(id, volunteer)) {
        std::cout << "\n\t\t\t\t\t\tID       : " << volunteer.getId();
        std::cout << "\n\t\t\t\t\t\tName     : " << volunteer.getName();
        std::cout << "\n\t\t\t\t\t\tSkill    : " << volunteer.getSkill();
        std::cout << "\n\t\t\t\t\t\tLocation : " << volunteer.getLocation();
        std::cout << "\n\t\t\t\t\t\tContact  : " << volunteer.getContact();
        std::cout << "\n\t\t\t\t\t\tStatus   : " << (volunteer.isAvailable() ? "Available" : "Busy") << "\n";
    } else {
        std::cout << "\n\t\t\t\t\t\tVolunteer Not Found.\n";
    }
}

void VolunteerMenu::updateVolunteer()
{
    int id;
    std::string name, skill, location, contact;
    char availableInput;
    bool available;
    std::cout << "\n\t\t\t\t\t\tVolunteer ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tName: ";
    std::getline(std::cin, name);
    std::cout << "\t\t\t\t\t\tSkill: ";
    std::getline(std::cin, skill);
    std::cout << "\t\t\t\t\t\tLocation: ";
    std::getline(std::cin, location);
    std::cout << "\t\t\t\t\t\tContact: ";
    std::getline(std::cin, contact);
    std::cout << "\t\t\t\t\t\tAvailable (y/n): ";
    std::cin >> availableInput;
    available = (availableInput == 'y' || availableInput == 'Y');
    if(volunteerService.updateVolunteer(id, name, skill, location, contact, available))
        std::cout << "\n\t\t\t\t\t\tUpdated Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tUpdate Failed.\n";
}

void VolunteerMenu::deleteVolunteer()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tVolunteer ID: ";
    std::cin >> id;
    if(volunteerService.deleteVolunteer(id))
        std::cout << "\n\t\t\t\t\t\tDeleted Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tDelete Failed.\n";
}

void VolunteerMenu::viewAvailableVolunteers()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Volunteer> volunteers;
    if (Core::AuthManager::isAdmin())
        volunteers = volunteerService.getAvailableVolunteers();
    else {
        Repositories::VolunteerRepository repo;
        auto all = repo.getByTenant(currentTenant);
        for(auto& v : all) {
            if(v.isAvailable()) volunteers.push_back(v);
        }
    }
    if(volunteers.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Available Volunteers.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\tAvailable Volunteers:\n";
    for(auto& v : volunteers) {
        std::cout << "\t\t\t\t\t\tID: " << v.getId()
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
    std::cout << "\n\t\t\t\t\t\tEnter Volunteer ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tEnter Task Description: ";
    std::getline(std::cin, task);
    if(volunteerService.assignTask(id, task))
        std::cout << "\n\t\t\t\t\t\tTask Assigned Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tTask Assignment Failed.\n";
}

}
}