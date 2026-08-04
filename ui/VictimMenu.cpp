#include "VictimMenu.h"
#include <iostream>
#include <iomanip>

namespace AgroResQ
{
    namespace UI
    {
        VictimMenu::VictimMenu() = default;

        void VictimMenu::show()
        {
            int choice;
            do
            {
                std::cout << "\n=========================================\n";
                std::cout << "            VICTIM MANAGEMENT\n";
                std::cout << "=========================================\n";
                std::cout << "1. Add Victim\n";
                std::cout << "2. View Victims\n";
                std::cout << "3. Search Victim\n";
                std::cout << "4. Update Victim\n";
                std::cout << "5. Delete Victim\n";
                std::cout << "6. Search Family\n";
                std::cout << "7. Missing Victims\n";
                std::cout << "8. Assign Shelter\n";
                std::cout << "9. Process Next Rescue\n";
                std::cout << "0. Back\n";
                std::cout << "=========================================\n";
                std::cout << "Enter Choice: ";
                std::cin >> choice;

                switch (choice)
                {
                case 1:
                    addVictim();
                    break;
                case 2:
                    viewAllVictims();
                    break;
                case 3:
                    searchVictim();
                    break;
                case 4:
                    updateVictim();
                    break;
                case 5:
                    deleteVictim();
                    break;
                case 6:
                    searchFamily();
                    break;
                case 7:
                    viewMissingVictims();
                    break;
                case 8:
                    assignShelter();
                    break;
                case 9:
                    processNextRescue();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "\nInvalid Choice.\n";
                }
            } while (choice != 0);
        }

        void VictimMenu::addVictim()
        {
            std::string name, gender, address, healthStatus;
            int age, familyId, priorityScore, shelterId;
            char vulnerableInput, disabledInput, rescuedInput, reliefInput, missingInput;
            bool vulnerable, disabled, rescued, reliefReceived, missing;

            std::cin.ignore();
            std::cout << "\nName: ";
            getline(std::cin, name);
            std::cout << "Age: ";
            std::cin >> age;
            std::cin.ignore();
            std::cout << "Gender: ";
            getline(std::cin, gender);
            std::cout << "Address: ";
            getline(std::cin, address);
            std::cout << "Vulnerable? (y/n): ";
            std::cin >> vulnerableInput;
            std::cout << "Family ID: ";
            std::cin >> familyId;
            std::cin.ignore();
            std::cout << "Health Status: ";
            getline(std::cin, healthStatus);
            std::cout << "Disabled? (y/n): ";
            std::cin >> disabledInput;
            std::cout << "Rescued? (y/n): ";
            std::cin >> rescuedInput;
            std::cout << "Relief Received? (y/n): ";
            std::cin >> reliefInput;
            std::cout << "Missing? (y/n): ";
            std::cin >> missingInput;
            std::cout << "Priority Score: ";
            std::cin >> priorityScore;
            std::cout << "Shelter ID: ";
            std::cin >> shelterId;

            vulnerable = (vulnerableInput == 'y' || vulnerableInput == 'Y');
            disabled = (disabledInput == 'y' || disabledInput == 'Y');
            rescued = (rescuedInput == 'y' || rescuedInput == 'Y');
            reliefReceived = (reliefInput == 'y' || reliefInput == 'Y');
            missing = (missingInput == 'y' || missingInput == 'Y');

            if (victimService.addVictim(name, age, gender, address, vulnerable, familyId,
                healthStatus, disabled, rescued, reliefReceived, missing,
                priorityScore, shelterId))
            {
                auto victims = victimService.getAllVictims();
                if (!victims.empty())
                {
                    int lastId = victims.back().getId();
                    if (!rescued && !missing)
                    {
                        rescueQueue.push(lastId);
                        std::cout << "\nVictim Added to Rescue Queue.\n";
                    }
                }
                std::cout << "\nVictim Added Successfully.\n";
            }
            else
            {
                std::cout << "\nFailed To Add Victim.\n";
            }
        }

        void VictimMenu::viewAllVictims()
        {
            auto victims = victimService.getAllVictims();
            if (victims.empty())
            {
                std::cout << "\nNo Victim Found.\n";
                return;
            }

            std::cout << "\n====================================================================\n";
            std::cout << std::left
                << std::setw(5) << "ID"
                << std::setw(20) << "Name"
                << std::setw(8) << "Age"
                << std::setw(15) << "Gender"
                << std::setw(20) << "Address"
                << std::setw(12) << "Priority"
                << "\n";
            std::cout << "====================================================================\n";

            for (auto& victim : victims)
            {
                std::cout << std::left
                    << std::setw(5) << victim.getId()
                    << std::setw(20) << victim.getName()
                    << std::setw(8) << victim.getAge()
                    << std::setw(15) << victim.getGender()
                    << std::setw(20) << victim.getAddress()
                    << std::setw(12) << (victim.isVulnerable() ? "High" : "Normal")
                    << "\n";
            }
        }

        void VictimMenu::searchVictim()
        {
            int id;
            std::cout << "\nVictim ID: ";
            std::cin >> id;

            Entities::Victim victim;
            if (victimService.searchVictim(id, victim))
            {
                std::cout << "\nID          : " << victim.getId();
                std::cout << "\nName        : " << victim.getName();
                std::cout << "\nAge         : " << victim.getAge();
                std::cout << "\nGender      : " << victim.getGender();
                std::cout << "\nAddress     : " << victim.getAddress();
                std::cout << "\nVulnerable  : " << (victim.isVulnerable() ? "Yes" : "No") << "\n";
                std::cout << "Missing     : " << (victim.isMissing() ? "Yes" : "No") << "\n";
                std::cout << "Rescued     : " << (victim.isRescued() ? "Yes" : "No") << "\n";
            }
            else
            {
                std::cout << "\nVictim Not Found.\n";
            }
        }

        void VictimMenu::updateVictim()
        {
            int id, age, familyId, priorityScore, shelterId;
            std::string name, gender, address, healthStatus;
            char vulnerableInput, disabledInput, rescuedInput, reliefInput, missingInput;
            bool vulnerable, disabled, rescued, reliefReceived, missing;

            std::cout << "\nVictim ID: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Name: ";
            getline(std::cin, name);
            std::cout << "Age: ";
            std::cin >> age;
            std::cin.ignore();
            std::cout << "Gender: ";
            getline(std::cin, gender);
            std::cout << "Address: ";
            getline(std::cin, address);
            std::cout << "Vulnerable? (y/n): ";
            std::cin >> vulnerableInput;
            std::cout << "Family ID: ";
            std::cin >> familyId;
            std::cin.ignore();
            std::cout << "Health Status: ";
            getline(std::cin, healthStatus);
            std::cout << "Disabled? (y/n): ";
            std::cin >> disabledInput;
            std::cout << "Rescued? (y/n): ";
            std::cin >> rescuedInput;
            std::cout << "Relief Received? (y/n): ";
            std::cin >> reliefInput;
            std::cout << "Missing? (y/n): ";
            std::cin >> missingInput;
            std::cout << "Priority Score: ";
            std::cin >> priorityScore;
            std::cout << "Shelter ID: ";
            std::cin >> shelterId;

            vulnerable = (vulnerableInput == 'y' || vulnerableInput == 'Y');
            disabled = (disabledInput == 'y' || disabledInput == 'Y');
            rescued = (rescuedInput == 'y' || rescuedInput == 'Y');
            reliefReceived = (reliefInput == 'y' || reliefInput == 'Y');
            missing = (missingInput == 'y' || missingInput == 'Y');

            if (victimService.updateVictim(id, name, age, gender, address, vulnerable, familyId,
                healthStatus, disabled, rescued, reliefReceived, missing,
                priorityScore, shelterId))
            {
                std::cout << "\nUpdated Successfully.\n";
            }
            else
            {
                std::cout << "\nUpdate Failed.\n";
            }
        }

        void VictimMenu::deleteVictim()
        {
            int id;
            std::cout << "\nVictim ID: ";
            std::cin >> id;

            if (victimService.deleteVictim(id))
            {
                std::cout << "\nDeleted Successfully.\n";
            }
            else
            {
                std::cout << "\nDelete Failed.\n";
            }
        }

        void VictimMenu::searchFamily()
        {
            int familyId;
            std::cout << "\nFamily ID: ";
            std::cin >> familyId;

            auto victims = victimService.getVictimsByFamily(familyId);
            if (victims.empty())
            {
                std::cout << "\nNo Family Members Found.\n";
                return;
            }

            std::cout << "\nFamily Members:\n";
            for (const auto& victim : victims)
            {
                std::cout << "ID: " << victim.getId()
                    << " | Name: " << victim.getName()
                    << " | Age: " << victim.getAge() << "\n";
            }
        }

        void VictimMenu::viewMissingVictims()
        {
            auto victims = victimService.getMissingVictims();
            if (victims.empty())
            {
                std::cout << "\nNo Missing Victims.\n";
                return;
            }

            std::cout << "\nMissing Victims:\n";
            for (const auto& victim : victims)
            {
                std::cout << "ID: " << victim.getId()
                    << " | Name: " << victim.getName()
                    << " | Location: " << victim.getAddress() << "\n";
            }
        }

        void VictimMenu::assignShelter()
        {
            int victimId, shelterId;
            std::cout << "\nVictim ID: ";
            std::cin >> victimId;
            std::cout << "Shelter ID: ";
            std::cin >> shelterId;

            if (victimService.assignShelter(victimId, shelterId))
            {
                std::cout << "\nShelter Assigned Successfully.\n";
            }
            else
            {
                std::cout << "\nAssignment Failed.\n";
            }
        }

        void VictimMenu::processNextRescue()
        {
            if (rescueQueue.isEmpty())
            {
                std::cout << "\nNo Victims in Rescue Queue.\n";
                return;
            }

            int victimId = rescueQueue.top();
            rescueQueue.pop();

            Entities::Victim victim;
            if (!victimService.searchVictim(victimId, victim))
            {
                std::cout << "\nVictim Not Found. Removing from Queue.\n";
                return;
            }

            std::cout << "\n========== PROCESSING RESCUE ==========\n";
            std::cout << "Victim ID    : " << victim.getId() << "\n";
            std::cout << "Name         : " << victim.getName() << "\n";
            std::cout << "Age          : " << victim.getAge() << "\n";
            std::cout << "Address      : " << victim.getAddress() << "\n";
            std::cout << "Priority     : " << victim.getPriorityScore() << "\n";
            std::cout << "Vulnerable   : " << (victim.isVulnerable() ? "Yes" : "No") << "\n";
            std::cout << "Disabled     : " << (victim.isDisabled() ? "Yes" : "No") << "\n";
            std::cout << "Health Status: " << victim.getHealthStatus() << "\n";

            char confirm;
            std::cout << "\nMark as Rescued? (y/n): ";
            std::cin >> confirm;

            if (confirm == 'y' || confirm == 'Y')
            {
                victim.setRescued(true);
                victimService.updateVictim(
                    victim.getId(),
                    victim.getName(),
                    victim.getAge(),
                    victim.getGender(),
                    victim.getAddress(),
                    victim.isVulnerable(),
                    victim.getFamilyId(),
                    victim.getHealthStatus(),
                    victim.isDisabled(),
                    true,
                    victim.hasReliefReceived(),
                    victim.isMissing(),
                    victim.getPriorityScore(),
                    victim.getShelterId()
                );
                std::cout << "\nVictim Marked as Rescued.\n";
            }
            else
            {
                std::cout << "\nRescue Cancelled. Victim remains in queue.\n";
                rescueQueue.push(victimId);
            }

            std::cout << "Remaining in Queue: " << rescueQueue.size() << "\n";
            std::cout << "=========================================\n";
        }
    }
}