#include "MainMenu.h"
#include "../core/Color.h"
#include <iostream>
#include <iomanip>

using namespace AgroResQ::Core;
namespace AgroResQ
{
    namespace UI
    {
        MainMenu::MainMenu() = default;

        void MainMenu::show()
        {
            int choice;
            do
            {
                std::cout << "\n=========================================\n";
                std::cout << "              AgroResQ SYSTEM\n";
                std::cout << "=========================================\n";
                std::cout << "1. Disaster Management\n";
                std::cout << "2. Victim Management\n";
                std::cout << "3. Shelter Management\n";
                std::cout << "4. Relief Management\n";
                std::cout << "5. Rescue Team Management\n";
                std::cout << "6. Agriculture Management\n";
                std::cout << "7. Volunteer Management\n";
                std::cout << "8. Family Management\n";
                std::cout << "9. Alert System\n";
                std::cout << "10. Route Optimization\n";
                std::cout << "11. Report Management\n";
                std::cout << "12. Dashboard\n";
                std::cout << "13. Budget Report\n";
                std::cout << "0. Exit\n";
                std::cout << "=========================================\n";
                std::cout << "Enter Choice: ";
                std::cin >> choice;

                switch (choice)
                {
                case 1:
                    disasterMenu.show();
                    break;
                case 2:
                    victimMenu.show();
                    break;
                case 3:
                    shelterMenu.show();
                    break;
                case 4:
                    reliefMenu.show();
                    break;
                case 5:
                    rescueTeamMenu.show();
                    break;
                case 6:
                    agricultureMenu.show();
                    break;
                case 7:
                    volunteerMenu.show();
                    break;
                case 8:
                    familyMenu.show();
                    break;
                case 9:
                    alertMenu.show();
                    break;
                case 10:
                    routeMenu.show();
                    break;
                case 11:
                    reportMenu.show();
                    break;
                case 12:
                    showDashboard();
                    break;
                case 13:
                    showBudgetReport();
                    break;
                case 0:
                    std::cout << "\nThank you for using AgroResQ.\n";
                    break;
                default:
                    std::cout << "\nInvalid Choice.\n";
                }
            } while (choice != 0);
        }

        void MainMenu::showDashboard()
        {
            std::cout << "\n============================================================\n";
            std::cout << "                    AGRO-RESQ DASHBOARD\n";
            std::cout << "============================================================\n";

            std::cout << "\n--- DISASTER STATISTICS ---\n";
            std::cout << "Total Disasters Recorded    : " << reportService.getTotalDisasters() << "\n";

            std::cout << "\n--- VICTIM STATISTICS ---\n";
            std::cout << "Total Victims Registered    : " << reportService.getTotalVictims() << "\n";
            std::cout << "Victims Rescued             : " << reportService.getRescuedVictimsCount() << "\n";
            std::cout << "Victims Missing             : " << reportService.getMissingVictimsCount() << "\n";
            std::cout << "Relief Received             : " << reportService.getReliefReceivedCount() << "\n";

            std::cout << "\n--- SHELTER STATISTICS ---\n";
            std::cout << "Total Shelters Available    : " << reportService.getTotalShelters() << "\n";
            std::cout << "Available Shelter Space     : " << reportService.getAvailableShelterSpace() << "\n";

            std::cout << "\n============================================================\n";

            if (reportService.getMissingVictimsCount() > 0)
            {
                std::cout << "\n[ALERT] " << reportService.getMissingVictimsCount()
                          << " victims are still missing! Immediate action required.\n";
            }

            if (reportService.getAvailableShelterSpace() < 10)
            {
                std::cout << "[WARNING] Shelter space is critically low!\n";
            }

            if (reportService.getTotalDisasters() == 0)
            {
                std::cout << "\n[INFO] No disasters recorded. System is on standby.\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }

        void MainMenu::showBudgetReport()
        {
            std::cout << budgetCalculator.generateBudgetReport();
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}