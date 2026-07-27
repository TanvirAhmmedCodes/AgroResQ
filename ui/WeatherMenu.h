#pragma once

#include "../services/WeatherService.h"

namespace AgroResQ
{
namespace UI
{

class WeatherMenu
{
private:
    Services::WeatherService weatherService;

    void addWeather();
    void viewAllWeather();
    void searchWeather();
    void updateWeather();
    void deleteWeather();

public:
    WeatherMenu();

    void show();
};

}
}