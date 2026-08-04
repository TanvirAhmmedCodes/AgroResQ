#pragma once

#include "../services/ShelterService.h"

namespace AgroResQ
{
namespace UI
{

class ShelterMenu
{
private:

    Services::ShelterService shelterService;

    void addShelter();

    void viewAllShelters();

    void searchShelter();

    void updateShelter();

    void deleteShelter();

    void viewAvailableShelters();

public:

    ShelterMenu();

    void show();
};

}
}