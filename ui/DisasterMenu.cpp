#include "DisasterMenu.h"
#include "../core/Color.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/disaster/DisasterRepository.h"
#include <iostream>
#include <iomanip>

using namespace AgroResQ::Core;

namespace AgroResQ
{
    namespace UI
    {
        static std::string DisasterType[] = {"", "Flood", "Cyclone", "Riverbank Erosion", "Earthquake", "Fire"};
        static std::string Divisions[] = {"", "Dhaka", "Chattogram", "Rajshahi", "Rangpur", "Khulna", "Barishal", "Sylhet", "Mymensingh"};
        static std::string Severity[] = {"", "Low", "Medium", "High", "Critical"};
        static std::string Status[] = {"", "Active", "Under Control", "Resolved"};

        static std::string dhakaDistricts[] = {"", "Dhaka", "Faridpur", "Gazipur", "Gopalganj", "Kishoreganj", "Madaripur", "Manikganj", "Munshiganj", "Narayanganj", "Narsingdi", "Rajbari", "Shariatpur", "Tangail"};
        static std::string chattogramDistricts[] = {"", "Chattogram", "Bandarban", "Brahmanbaria", "Chandpur", "Cumilla", "Coxsbazar", "Feni", "Khagrachari", "Lakshmipur", "Noakhali", "Rangamati"};
        static std::string rajshahiDistricts[] = {"", "Rajshahi", "Bogura", "Joypurhat", "Naogaon", "Natore", "Chapainawabganj", "Pabna", "Sirajganj"};
        static std::string rangpurDistricts[] = {"", "Rangpur", "Dinajpur", "Gaibandha", "Kurigram", "Lalmonirhat", "Nilphamari", "Panchagarh", "Thakurgaon"};
        static std::string khulnaDistricts[] = {"", "Khulna", "Bagerhat", "Chuadanga", "Jashore", "Jhenaidah", "Kushtia", "Magura", "Meherpur", "Narail", "Satkhira"};
        static std::string barishalDistricts[] = {"", "Barishal", "Barguna", "Bhola", "Jhalakathi", "Patuakhali", "Pirojpur"};
        static std::string sylhetDistricts[] = {"", "Sylhet", "Habiganj", "Moulivibazar", "Sunamganj"};
        static std::string mymensinghDistricts[] = {"", "Mymensingh", "Jamalpur", "Netrokona", "Sherpur"};

        static std::string* allDistricts[] = {nullptr, dhakaDistricts, chattogramDistricts, rajshahiDistricts, rangpurDistricts, khulnaDistricts, barishalDistricts, sylhetDistricts, mymensinghDistricts};
        static int districtCount[] = {0, 13, 11, 8, 8, 10, 6, 4, 4};

        int inputChoice(int min, int max)
        {
            int value;
            while (true)
            {
                std::cin >> value;
                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << Color::red() << "\n\t\t\t\t\t\tInvalid input. Enter again: " << Color::reset();
                }
                else if (value < min || value > max)
                {
                    std::cout << Color::yellow() << "\n\t\t\t\t\t\tInvalid Choice. Enter again: " << Color::reset();
                }
                else
                {
                    return value;
                }
            }
        }

        int inputPositiveInteger()
        {
            int value;
            while (true)
            {
                std::cin >> value;
                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << Color::red() << "\n\t\t\t\t\t\tInvalid input. Enter again: " << Color::reset();
                }
                else if (value < 0)
                {
                    std::cout << Color::yellow() << "\n\t\t\t\t\t\tValue cannot be negative. Enter again: " << Color::reset();
                }
                else
                {
                    return value;
                }
            }
        }

        DisasterMenu::DisasterMenu() = default;

        void DisasterMenu::show()
        {
            int choice;
            do
            {
                std::cout << Color::boldCyan()
                          << "\n=========================================\n"
                          << Color::boldYellow()
                          << "        DISASTER MANAGEMENT MENU\n"
                          << Color::boldCyan()
                          << "=========================================\n"
                          << Color::reset();

                std::cout << Color::green() << "1." << Color::reset() << " Add Disaster\n";
                std::cout << Color::green() << "2." << Color::reset() << " View All Disasters\n";
                std::cout << Color::green() << "3." << Color::reset() << " Search Disaster\n";
                std::cout << Color::green() << "4." << Color::reset() << " Update Disaster\n";
                std::cout << Color::green() << "5." << Color::reset() << " Delete Disaster\n";
                std::cout << Color::red() << "0." << Color::reset() << " Back\n";

                std::cout << Color::boldCyan()
                          << "=========================================\n"
                          << Color::reset();

                std::cout << Color::yellow() << "Enter Choice: " << Color::reset();
                std::cin >> choice;

                switch (choice)
                {
                case 1: addDisaster(); break;
                case 2: viewAllDisasters(); break;
                case 3: searchDisaster(); break;
                case 4: updateDisaster(); break;
                case 5: deleteDisaster(); break;
                case 0: break;
                default:
                    std::cout << Color::red() << "\nInvalid Choice!\n" << Color::reset();
                }

                if (choice != 0)
                {
                    std::cout << "\n\n\t\t\t\t\t\tPress Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                }

            } while (choice != 0);
        }

        void DisasterMenu::addDisaster()
        {
            std::string name, date;
            int severity, division, district, disasterType, affectedPeople, status;

            std::cout << Color::boldCyan()
                      << "\n\n\t\t\t\t\t\t----Register Disaster----\n"
                      << Color::reset();
            std::cout << "\n\t\t\t\t\t\tEnter Disaster Details.\n";

            std::cin.ignore();
            std::cout << "\n\t\t\t\t\t\tEnter Disaster Name: ";
            std::getline(std::cin, name);

            std::cout << "\n\t\t\t\t\t\tSelect Disaster Type:\n";
            std::cout << "\t\t\t\t\t\t1. Flood\n\t\t\t\t\t\t2. Cyclone\n\t\t\t\t\t\t3. Riverbank Erosion\n\t\t\t\t\t\t4. Earthquake\n\t\t\t\t\t\t5. Fire";
            std::cout << "\n\t\t\t\t\t\tEnter your choice: ";
            disasterType = inputChoice(1, 5);

            std::cout << "\n\t\t\t\t\t\tSelect Division:\n";
            std::cout << "\t\t\t\t\t\t1. Dhaka\n\t\t\t\t\t\t2. Chattogram\n\t\t\t\t\t\t3. Rajshahi\n\t\t\t\t\t\t4. Rangpur\n\t\t\t\t\t\t5. Khulna\n\t\t\t\t\t\t6. Barishal\n\t\t\t\t\t\t7. Sylhet\n\t\t\t\t\t\t8. Mymensingh";
            std::cout << "\n\t\t\t\t\t\tEnter your choice: ";
            division = inputChoice(1, 8);

            std::cout << "\n\t\t\t\t\t\tSelect District:\n";
            for (int i = 1; i <= districtCount[division]; i++)
            {
                std::cout << "\t\t\t\t\t\t" << i << ". " << allDistricts[division][i] << "\n";
            }
            std::cout << "\t\t\t\t\t\tEnter your choice: ";
            district = inputChoice(1, districtCount[division]);

            std::cout << "\n\t\t\t\t\t\tEnter Date (DD-MM-YYYY): ";
            std::cin >> date;

            std::cout << "\n\t\t\t\t\t\tSelect Severity:\n";
            std::cout << "\t\t\t\t\t\t1. Low\n\t\t\t\t\t\t2. Medium\n\t\t\t\t\t\t3. High\n\t\t\t\t\t\t4. Critical";
            std::cout << "\n\t\t\t\t\t\tEnter your choice: ";
            severity = inputChoice(1, 4);

            std::cout << "\n\t\t\t\t\t\tEnter number of affected people (estimated): ";
            affectedPeople = inputPositiveInteger();

            std::cout << "\n\t\t\t\t\t\tSelect Status:\n";
            std::cout << "\t\t\t\t\t\t1. Active\n\t\t\t\t\t\t2. Under Control\n\t\t\t\t\t\t3. Resolved";
            std::cout << "\n\t\t\t\t\t\tEnter your choice: ";
            status = inputChoice(1, 3);

            std::string location = allDistricts[division][district];
            std::string type = DisasterType[disasterType];

            if (disasterService.addDisaster(name, type, location, date, severity,
                                            division, district, disasterType, affectedPeople, status))
            {
                std::cout << Color::green()
                          << "\n\n\t\t\t\t\t\tDisaster Registered Successfully!\n"
                          << Color::reset();

                std::cout << Color::boldCyan()
                          << "\n\n\t\t\t\t\t\t----Disaster Details----\n"
                          << Color::reset();
                std::cout << "\n\t\t\t\t\t\tDisaster Name: " << name;
                std::cout << "\n\t\t\t\t\t\tDisaster Type: " << DisasterType[disasterType];
                std::cout << "\n\t\t\t\t\t\tDivision: " << Divisions[division];
                std::cout << "\n\t\t\t\t\t\tDistrict: " << allDistricts[division][district];
                std::cout << "\n\t\t\t\t\t\tDate: " << date;
                std::cout << "\n\t\t\t\t\t\tSeverity: " << Severity[severity];
                std::cout << "\n\t\t\t\t\t\tAffected People: " << affectedPeople;
                std::cout << "\n\t\t\t\t\t\tStatus: " << Status[status] << "\n";
            }
            else
            {
                std::cout << Color::red()
                          << "\n\t\t\t\t\t\tFailed to Register Disaster.\n"
                          << Color::reset();
            }
        }

        void DisasterMenu::viewAllDisasters()
        {
            std::string currentTenant = Core::TenantManager::getCurrentTenant();
            std::vector<Entities::Disaster> disasters;
            if (Core::AuthManager::isAdmin())
                disasters = disasterService.getAllDisasters();
            else {
                Repositories::DisasterRepository repo;
                disasters = repo.getByTenant(currentTenant);
            }

            if (disasters.empty())
            {
                std::cout << Color::yellow()
                          << "\n\t\t\t\t\t\tNo Disaster Found.\n"
                          << Color::reset();
                return;
            }

            std::cout << Color::boldCyan()
                      << "\n\n\t\t\t\t\t\t----All Disasters----\n"
                      << Color::reset();
            std::cout << "\t\t\t\t\t\t------------------------------------------------------------\n";

            for (const auto& d : disasters)
            {
                std::cout << "\t\t\t\t\t\tID: " << d.getId()
                          << " | Name: " << d.getName()
                          << " | Type: " << d.getType()
                          << " | Location: " << d.getLocation()
                          << " | Severity: " << d.getSeverity()
                          << " | Status: " << d.getStatusName()
                          << "\n";
            }
        }

        void DisasterMenu::searchDisaster()
        {
            int id;
            std::cout << "\n\t\t\t\t\t\tEnter Disaster ID: ";
            std::cin >> id;

            Entities::Disaster d;
            if (disasterService.searchDisaster(id, d))
            {
                std::cout << Color::boldCyan()
                          << "\n\n\t\t\t\t\t\t----Disaster Details----\n"
                          << Color::reset();
                std::cout << "\n\t\t\t\t\t\tID: " << d.getId();
                std::cout << "\n\t\t\t\t\t\tName: " << d.getName();
                std::cout << "\n\t\t\t\t\t\tType: " << d.getType();
                std::cout << "\n\t\t\t\t\t\tLocation: " << d.getLocation();
                std::cout << "\n\t\t\t\t\t\tDate: " << d.getDate();
                std::cout << "\n\t\t\t\t\t\tSeverity: " << d.getSeverityName();
                std::cout << "\n\t\t\t\t\t\tDivision: " << d.getDivisionName();
                std::cout << "\n\t\t\t\t\t\tDistrict: " << d.getDistrictName();
                std::cout << "\n\t\t\t\t\t\tDisaster Type: " << d.getDisasterTypeName();
                std::cout << "\n\t\t\t\t\t\tAffected People: " << d.getAffectedPeople();
                std::cout << "\n\t\t\t\t\t\tStatus: " << d.getStatusName() << "\n";
            }
            else
            {
                std::cout << Color::red()
                          << "\n\t\t\t\t\t\tDisaster Not Found.\n"
                          << Color::reset();
            }
        }

        void DisasterMenu::updateDisaster()
        {
            int id;
            std::cout << "\n\t\t\t\t\t\tEnter Disaster ID: ";
            std::cin >> id;

            Entities::Disaster d;
            if (!disasterService.searchDisaster(id, d))
            {
                std::cout << Color::red()
                          << "\n\t\t\t\t\t\tDisaster Not Found.\n"
                          << Color::reset();
                return;
            }

            std::string name, date;
            int severity, division, district, disasterType, affectedPeople, status;

            std::cin.ignore();
            std::cout << "\n\t\t\t\t\t\tEnter New Details:\n";

            std::cout << "\t\t\t\t\t\tName [" << d.getName() << "]: ";
            std::getline(std::cin, name);
            if (name.empty()) name = d.getName();

            std::cout << "\n\t\t\t\t\t\tSelect Disaster Type:\n";
            std::cout << "\t\t\t\t\t\t1. Flood\n\t\t\t\t\t\t2. Cyclone\n\t\t\t\t\t\t3. Riverbank Erosion\n\t\t\t\t\t\t4. Earthquake\n\t\t\t\t\t\t5. Fire";
            std::cout << "\n\t\t\t\t\t\tEnter your choice [" << d.getDisasterType() << "]: ";
            disasterType = inputChoice(1, 5);

            std::cout << "\n\t\t\t\t\t\tSelect Division:\n";
            std::cout << "\t\t\t\t\t\t1. Dhaka\n\t\t\t\t\t\t2. Chattogram\n\t\t\t\t\t\t3. Rajshahi\n\t\t\t\t\t\t4. Rangpur\n\t\t\t\t\t\t5. Khulna\n\t\t\t\t\t\t6. Barishal\n\t\t\t\t\t\t7. Sylhet\n\t\t\t\t\t\t8. Mymensingh";
            std::cout << "\n\t\t\t\t\t\tEnter your choice [" << d.getDivision() << "]: ";
            division = inputChoice(1, 8);

            std::cout << "\n\t\t\t\t\t\tSelect District:\n";
            for (int i = 1; i <= districtCount[division]; i++)
            {
                std::cout << "\t\t\t\t\t\t" << i << ". " << allDistricts[division][i] << "\n";
            }
            std::cout << "\t\t\t\t\t\tEnter your choice [" << d.getDistrict() << "]: ";
            district = inputChoice(1, districtCount[division]);

            std::cout << "\n\t\t\t\t\t\tEnter Date (DD-MM-YYYY) [" << d.getDate() << "]: ";
            std::cin >> date;
            if (date.empty()) date = d.getDate();

            std::cout << "\n\t\t\t\t\t\tSelect Severity:\n";
            std::cout << "\t\t\t\t\t\t1. Low\n\t\t\t\t\t\t2. Medium\n\t\t\t\t\t\t3. High\n\t\t\t\t\t\t4. Critical";
            std::cout << "\n\t\t\t\t\t\tEnter your choice [" << d.getSeverity() << "]: ";
            severity = inputChoice(1, 4);

            std::cout << "\n\t\t\t\t\t\tEnter number of affected people [" << d.getAffectedPeople() << "]: ";
            affectedPeople = inputPositiveInteger();

            std::cout << "\n\t\t\t\t\t\tSelect Status:\n";
            std::cout << "\t\t\t\t\t\t1. Active\n\t\t\t\t\t\t2. Under Control\n\t\t\t\t\t\t3. Resolved";
            std::cout << "\n\t\t\t\t\t\tEnter your choice [" << d.getStatus() << "]: ";
            status = inputChoice(1, 3);

            std::string location = allDistricts[division][district];
            std::string type = DisasterType[disasterType];

            if (disasterService.updateDisaster(id, name, type, location, date, severity,
                                               division, district, disasterType, affectedPeople, status))
            {
                std::cout << Color::green()
                          << "\n\t\t\t\t\t\tUpdated Successfully.\n"
                          << Color::reset();
            }
            else
            {
                std::cout << Color::red()
                          << "\n\t\t\t\t\t\tUpdate Failed.\n"
                          << Color::reset();
            }
        }

        void DisasterMenu::deleteDisaster()
        {
            int id;
            std::cout << "\n\t\t\t\t\t\tEnter Disaster ID: ";
            std::cin >> id;

            if (disasterService.deleteDisaster(id))
            {
                std::cout << Color::green()
                          << "\n\t\t\t\t\t\tDeleted Successfully.\n"
                          << Color::reset();
            }
            else
            {
                std::cout << Color::red()
                          << "\n\t\t\t\t\t\tDelete Failed.\n"
                          << Color::reset();
            }
        }
    }
}