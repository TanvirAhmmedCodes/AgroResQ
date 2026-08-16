#include "MainMenu.h"
#include "../core/Color.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../graphics/WinDashboard.h"
#include <iostream>
#include <iomanip>

using namespace AgroResQ::Core;

namespace AgroResQ
{
    namespace UI
    {
        MainMenu::MainMenu() : licenseManager(Business::LicenseTier::GOVERNMENT) {}

        bool MainMenu::hasAccessToFeature(const std::string &featureName)
        {
            auto user = AuthManager::getCurrentUser();
            if (user.role == UserRole::ADMIN)
                return true;
            if (user.role == UserRole::NGO_OPERATOR)
            {
                if (featureName == "PARTNER_ANALYTICS" || featureName == "BUDGET_REPORT")
                    return false;
                return true;
            }
            if (user.role == UserRole::FARMER)
            {
                if (featureName == "DISASTER_MANAGEMENT" ||
                    featureName == "VICTIM_MANAGEMENT" ||
                    featureName == "SHELTER_MANAGEMENT" ||
                    featureName == "RELIEF_MANAGEMENT" ||
                    featureName == "RESCUE_TEAM" ||
                    featureName == "VOLUNTEER_MANAGEMENT" ||
                    featureName == "FAMILY_MANAGEMENT" ||
                    featureName == "ROUTE_OPTIMIZATION" ||
                    featureName == "BUDGET_REPORT" ||
                    featureName == "PARTNER_ANALYTICS")
                    return false;
                return true;
            }
            return false;
        }

        void MainMenu::show()
        {
            int choice;
            do
            {
                std::cout << "\n=========================================\n";
                std::cout << "              AgroResQ SYSTEM\n";
                std::cout << "=========================================\n";
                std::cout << Color::boldGreen() << "User: " << AuthManager::getCurrentUser().username
                          << " | Tenant: " << TenantManager::getCurrentTenant()
                          << " | Role: ";
                if (AuthManager::isAdmin())
                    std::cout << "ADMIN";
                else if (AuthManager::isNGO())
                    std::cout << "NGO";
                else
                    std::cout << "FARMER";
                std::cout << Color::reset() << "\n";
                std::cout << "=========================================\n";

                int menuIndex = 1;
                if (hasAccessToFeature("DISASTER_MANAGEMENT"))
                    std::cout << menuIndex++ << ". Disaster Management\n";
                if (hasAccessToFeature("VICTIM_MANAGEMENT"))
                    std::cout << menuIndex++ << ". Victim Management\n";
                if (hasAccessToFeature("SHELTER_MANAGEMENT"))
                    std::cout << menuIndex++ << ". Shelter Management\n";
                if (hasAccessToFeature("RELIEF_MANAGEMENT"))
                    std::cout << menuIndex++ << ". Relief Management\n";
                if (hasAccessToFeature("RESCUE_TEAM"))
                    std::cout << menuIndex++ << ". Rescue Team Management\n";
                if (hasAccessToFeature("AGRICULTURE"))
                    std::cout << menuIndex++ << ". Agriculture Management\n";
                if (hasAccessToFeature("VOLUNTEER_MANAGEMENT"))
                    std::cout << menuIndex++ << ". Volunteer Management\n";
                if (hasAccessToFeature("FAMILY_MANAGEMENT"))
                    std::cout << menuIndex++ << ". Family Management\n";
                if (hasAccessToFeature("ALERT"))
                    std::cout << menuIndex++ << ". Alert System\n";
                if (hasAccessToFeature("ROUTE_OPTIMIZATION"))
                    std::cout << menuIndex++ << ". Route Optimization\n";
                if (hasAccessToFeature("REPORT"))
                    std::cout << menuIndex++ << ". Report Management\n";
                if (hasAccessToFeature("DASHBOARD"))
                    std::cout << menuIndex++ << ". Dashboard\n";
                if (hasAccessToFeature("BUDGET_REPORT"))
                    std::cout << menuIndex++ << ". Budget Report\n";
                if (hasAccessToFeature("PARTNER_ANALYTICS"))
                    std::cout << menuIndex++ << ". Partner Analytics\n";
                std::cout << "0. Logout & Exit\n";
                std::cout << "=========================================\n";
                std::cout << "Enter Choice: ";
                std::cin >> choice;

                switch (choice)
                {
                case 1:
                    if (hasAccessToFeature("DISASTER_MANAGEMENT"))
                        disasterMenu.show();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 2:
                    if (hasAccessToFeature("VICTIM_MANAGEMENT"))
                        victimMenu.show();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 3:
                    if (hasAccessToFeature("SHELTER_MANAGEMENT"))
                        shelterMenu.show();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 4:
                    if (hasAccessToFeature("RELIEF_MANAGEMENT"))
                        reliefMenu.show();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 5:
                    if (hasAccessToFeature("RESCUE_TEAM"))
                        rescueTeamMenu.show();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 6:
                    if (hasAccessToFeature("AGRICULTURE"))
                        agricultureMenu.show();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 7:
                    if (hasAccessToFeature("VOLUNTEER_MANAGEMENT"))
                        volunteerMenu.show();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 8:
                    if (hasAccessToFeature("FAMILY_MANAGEMENT"))
                        familyMenu.show();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 9:
                    if (hasAccessToFeature("ALERT"))
                        alertMenu.show();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 10:
                    if (hasAccessToFeature("ROUTE_OPTIMIZATION"))
                        routeMenu.show();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 11:
                    if (hasAccessToFeature("REPORT"))
                        reportMenu.show();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 12:
                    if (hasAccessToFeature("DASHBOARD"))
                        winDashboard.show();   // ===== Windows Native Dashboard =====
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 13:
                    if (hasAccessToFeature("BUDGET_REPORT"))
                        showBudgetReport();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 14:
                    if (hasAccessToFeature("PARTNER_ANALYTICS"))
                        showPartnerReport();
                    else
                        std::cout << "\n\t\t\t\t\t\tAccess Denied.\n";
                    break;
                case 0:
                    AuthManager::logout();
                    std::cout << "\n\t\t\t\t\t\tLogged out. Thank you for using AgroResQ.\n";
                    break;
                default:
                    std::cout << "\n\t\t\t\t\t\tInvalid Choice.\n";
                }
            } while (choice != 0);
        }

        void MainMenu::showPartnerReport()
        {
            if (!hasAccessToFeature("PARTNER_ANALYTICS"))
            {
                std::cout << "\t\t\t\t\t\tAccess Denied.\n";
                return;
            }
            std::cout << "\n\t\t\t\t\t\t--- PARTNER ANALYTICS (AGGREGATED) ---\n";

            std::string tenantId = Core::TenantManager::getCurrentTenant();
            std::cout << "\t\t\t\t\t\t" << partnerAnalytics.generateCsvReport("", tenantId) << std::endl;
            std::cout << "\t\t\t\t\t\t----------------------------------------\n";
        }

        void MainMenu::showBudgetReport()
        {
            if (!hasAccessToFeature("BUDGET_REPORT"))
            {
                std::cout << "\t\t\t\t\t\tAccess Denied.\n";
                return;
            }
            std::cout << budgetCalculator.generateBudgetReport();
            std::cout << "\n\t\t\t\t\t\tPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}