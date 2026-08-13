#pragma once

#include "../algorithms/DecisionSupportEngine.h"

#include "../entities/Soil.h"
#include "../entities/Weather.h"


namespace AgroResQ
{
namespace UI
{

class DecisionSupportMenu
{

private:

    Algorithms::DecisionSupportEngine engine;


    void generateDecision();


public:

    DecisionSupportMenu();


    void show();

};

}
}