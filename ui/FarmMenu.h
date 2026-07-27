#pragma once

#include "../services/AgricultureService.h"

namespace AgroResQ
{
namespace UI
{

class FarmMenu
{
private:

    Services::AgricultureService agricultureService;

    void addFarm();

    void viewAllFarms();

    void searchFarm();

    void updateFarm();

    void deleteFarm();

public:

    FarmMenu();

    void show();
};

}
}