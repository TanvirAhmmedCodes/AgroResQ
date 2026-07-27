#include "WeatherMenu.h"

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
        case 1:
            addWeather();
            break;

        case 2:
            viewAllWeather();
            break;

        case 3:
            searchWeather();
            break;

        case 4:
            updateWeather();
            break;

        case 5:
            deleteWeather();
            break;

        case 0:
            break;

        default:
            std::cout << "\nInvalid Choice.\n";
        }

    } while(choice != 0);
}


void WeatherMenu::addWeather()
{
    std::string location;

    double temperature;
    double humidity;
    double rainfall;


    std::cin.ignore();

    std::cout << "\nLocation: ";
    std::getline(std::cin, location);

    std::cout << "Temperature: ";
    std::cin >> temperature;

    std::cout << "Humidity: ";
    std::cin >> humidity;

    std::cout << "Rainfall: ";
    std::cin >> rainfall;


    if(weatherService.addWeather(
        location,
        temperature,
        humidity,
        rainfall))
    {
        std::cout << "\nWeather Data Added Successfully.\n";
    }
    else
    {
        std::cout << "\nFailed To Add Weather Data.\n";
    }
}


void WeatherMenu::viewAllWeather()
{
    std::vector<Entities::Weather> weatherList =
        weatherService.getAllWeather();


    if(weatherList.empty())
    {
        std::cout << "\nNo Weather Data Found.\n";
        return;
    }


    std::cout << "\n====================================================================\n";

    std::cout
        << std::left
        << std::setw(5) << "ID"
        << std::setw(20) << "Location"
        << std::setw(15) << "Temp"
        << std::setw(15) << "Humidity"
        << std::setw(15) << "Rainfall"
        << "\n";


    std::cout << "====================================================================\n";


    for(const auto& weather : weatherList)
    {
        std::cout
            << std::left
            << std::setw(5) << weather.getId()
            << std::setw(20) << weather.getLocation()
            << std::setw(15) << weather.getTemperature()
            << std::setw(15) << weather.getHumidity()
            << std::setw(15) << weather.getRainfall()
            << "\n";
    }
}


void WeatherMenu::searchWeather()
{
    int id;

    std::cout << "\nWeather ID: ";
    std::cin >> id;


    Entities::Weather weather;


    if(weatherService.searchWeather(id, weather))
    {
        std::cout << "\nID          : " << weather.getId();
        std::cout << "\nLocation    : " << weather.getLocation();
        std::cout << "\nTemperature : " << weather.getTemperature();
        std::cout << "\nHumidity    : " << weather.getHumidity();
        std::cout << "\nRainfall    : " << weather.getRainfall() << "\n";
    }
    else
    {
        std::cout << "\nWeather Data Not Found.\n";
    }
}


void WeatherMenu::updateWeather()
{
    int id;

    std::string location;

    double temperature;
    double humidity;
    double rainfall;


    std::cout << "\nWeather ID: ";
    std::cin >> id;

    std::cin.ignore();

    std::cout << "Location: ";
    std::getline(std::cin, location);

    std::cout << "Temperature: ";
    std::cin >> temperature;

    std::cout << "Humidity: ";
    std::cin >> humidity;

    std::cout << "Rainfall: ";
    std::cin >> rainfall;



    if(weatherService.updateWeather(
        id,
        location,
        temperature,
        humidity,
        rainfall))
    {
        std::cout << "\nUpdated Successfully.\n";
    }
    else
    {
        std::cout << "\nUpdate Failed.\n";
    }
}


void WeatherMenu::deleteWeather()
{
    int id;

    std::cout << "\nWeather ID: ";
    std::cin >> id;


    if(weatherService.deleteWeather(id))
    {
        std::cout << "\nDeleted Successfully.\n";
    }
    else
    {
        std::cout << "\nDelete Failed.\n";
    }
}

}
}