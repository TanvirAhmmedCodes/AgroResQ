#pragma once

#include "../services/SoilService.h"

namespace AgroResQ
{
namespace UI
{

class SoilMenu
{
private:
    Services::SoilService soilService;

    void addSoil();
    void viewAllSoils();
    void searchSoil();
    void updateSoil();
    void deleteSoil();

public:
    SoilMenu();

    void show();
};

}
}