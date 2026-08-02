#pragma once

#include "../services/ReliefService.h"

namespace AgroResQ
{
namespace UI
{

class ReliefMenu
{
private:

    Services::ReliefService reliefService;

    void addRelief();

    void viewAllRelief();

    void searchRelief();

    void updateRelief();

    void deleteRelief();

public:

    ReliefMenu();

    void show();
};

}
}