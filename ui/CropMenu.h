#pragma once

#include "../services/CropService.h"

namespace AgroResQ
{
namespace UI
{

class CropMenu
{
private:
    Services::CropService cropService;

    void addCrop();
    void viewAllCrops();
    void searchCrop();
    void updateCrop();
    void deleteCrop();

public:
    CropMenu();

    void show();
};

}
}