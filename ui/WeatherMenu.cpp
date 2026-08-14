#include "WeatherMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/agriculture/WeatherRepository.h"
#include <iomanip>
#include <iostream>

namespace AgroResQ
{
namespace UI
{

WeatherMenu::WeatherMenu() = default;

void WeatherMenu::show()
{
    int choice;
    do
    {
        std::cout << "\n=========================================\n";
        std::cout << "            WEATHER MANAGEMENT\n";
        std::cout << "=========================================\n";
        std::cout << "1. Add Weather Data\n";
        std::cout << "2. View Weather Data\n";
        std::cout << "3. Search Weather\n";
        std::cout << "4. Update Weather\n";
        std::cout << "5. Delete Weather\n";
        std::cout << "0. Back\n";
        std::cout << "=========================================\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
        case 1: addWeather(); break;
        case 2: viewAllWeather(); break;
        case 3: searchWeather(); break;
        case 4: updateWeather(); break;
        case 5: deleteWeather(); break;
        case 0: break;
        default: std::cout << "\nInvalid Choice.\n";
        }
    } while(choice != 0);
}

void WeatherMenu::addWeather()
{
    std::string location;
    double temperature, humidity, rainfall;
    std::cin.ignore();
    std::cout << "\n\t\t\t\t\t\tLocation: ";
    std::getline(std::cin, location);
    std::cout << "\t\t\t\t\t\tTemperature: ";
    std::cin >> temperature;
    std::cout << "\t\t\t\t\t\tHumidity: ";
    std::cin >> humidity;
    std::cout << "\t\t\t\t\t\tRainfall: ";
    std::cin >> rainfall;
    if(weatherService.addWeather(location, temperature, humidity, rainfall))
        std::cout << "\n\t\t\t\t\t\tWeather Data Added Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tFailed To Add Weather Data.\n";
}

void WeatherMenu::viewAllWeather()
{
    std::string currentTenant = Core::TenantManager::getCurrentTenant();
    std::vector<Entities::Weather> weatherList;
    if (Core::AuthManager::isAdmin())
        weatherList = weatherService.getAllWeather();
    else {
        Repositories::WeatherRepository repo;
        weatherList = repo.getByTenant(currentTenant);
    }
    if(weatherList.empty()) {
        std::cout << "\n\t\t\t\t\t\tNo Weather Data Found.\n";
        return;
    }
    std::cout << "\n\t\t\t\t\t\t====================================================================\n";
    std::cout << "\t\t\t\t\t\tID\tLocation\t\tTemp\t\tHumidity\tRainfall\n";
    std::cout << "\t\t\t\t\t\t====================================================================\n";
    for(const auto& w : weatherList) {
        std::cout << "\t\t\t\t\t\t" << w.getId() << "\t"
                  << w.getLocation() << "\t\t"
                  << w.getTemperature() << "\t\t"
                  << w.getHumidity() << "\t\t"
                  << w.getRainfall() << "\n";
    }
}

void WeatherMenu::searchWeather()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tWeather ID: ";
    std::cin >> id;
    Entities::Weather weather;
    if(weatherService.searchWeather(id, weather)) {
        std::cout << "\n\t\t\t\t\t\tID          : " << weather.getId();
        std::cout << "\n\t\t\t\t\t\tLocation    : " << weather.getLocation();
        std::cout << "\n\t\t\t\t\t\tTemperature : " << weather.getTemperature();
        std::cout << "\n\t\t\t\t\t\tHumidity    : " << weather.getHumidity();
        std::cout << "\n\t\t\t\t\t\tRainfall    : " << weather.getRainfall() << "\n";
    } else {
        std::cout << "\n\t\t\t\t\t\tWeather Data Not Found.\n";
    }
}

void WeatherMenu::updateWeather()
{
    int id;
    std::string location;
    double temperature, humidity, rainfall;
    std::cout << "\n\t\t\t\t\t\tWeather ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "\t\t\t\t\t\tLocation: ";
    std::getline(std::cin, location);
    std::cout << "\t\t\t\t\t\tTemperature: ";
    std::cin >> temperature;
    std::cout << "\t\t\t\t\t\tHumidity: ";
    std::cin >> humidity;
    std::cout << "\t\t\t\t\t\tRainfall: ";
    std::cin >> rainfall;
    if(weatherService.updateWeather(id, location, temperature, humidity, rainfall))
        std::cout << "\n\t\t\t\t\t\tUpdated Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tUpdate Failed.\n";
}

void WeatherMenu::deleteWeather()
{
    int id;
    std::cout << "\n\t\t\t\t\t\tWeather ID: ";
    std::cin >> id;
    if(weatherService.deleteWeather(id))
        std::cout << "\n\t\t\t\t\t\tDeleted Successfully.\n";
    else
        std::cout << "\n\t\t\t\t\t\tDelete Failed.\n";
}

}
}