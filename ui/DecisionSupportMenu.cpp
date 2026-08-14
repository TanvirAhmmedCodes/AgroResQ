#include "DecisionSupportMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include <iostream>

namespace AgroResQ
{
namespace UI
{

DecisionSupportMenu::DecisionSupportMenu() = default;

void DecisionSupportMenu::show()
{
    int choice;

    do
    {
        std::cout << "\n=========================================\n";
        std::cout << "        DECISION SUPPORT SYSTEM\n";
        std::cout << "=========================================\n";
        std::cout << "1. Generate Agriculture Report\n";
        std::cout << "0. Back\n";
        std::cout << "=========================================\n";
        std::cout << "Enter Choice: ";

        std::cin >> choice;

        switch(choice)
        {
        case 1:
            generateDecision();
            break;
        case 0:
            break;
        default:
            std::cout << "\n\t\t\t\t\t\tInvalid Choice.\n";
        }
    } while(choice != 0);
}

void DecisionSupportMenu::generateDecision()
{
    double ph;
    double moisture;
    double temperature;
    double humidity;
    double rainfall;

    std::cout << "\n\t\t\t\t\t\tEnter Soil PH Level: ";
    std::cin >> ph;
    std::cout << "\t\t\t\t\t\tEnter Soil Moisture (%): ";
    std::cin >> moisture;
    std::cout << "\t\t\t\t\t\tEnter Temperature: ";
    std::cin >> temperature;
    std::cout << "\t\t\t\t\t\tEnter Humidity (%): ";
    std::cin >> humidity;
    std::cout << "\t\t\t\t\t\tEnter Rainfall: ";
    std::cin >> rainfall;

    Entities::Soil soil(0, "TEMP", ph, moisture, "Unknown");
    Entities::Weather weather(0, "TEMP", temperature, humidity, rainfall);

    std::cout << "\n";
    std::cout << engine.generateReport(soil, weather);
}

}
}