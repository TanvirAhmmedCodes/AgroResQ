#pragma once

#include <string>

#include "../entities/Soil.h"
#include "../entities/Weather.h"

namespace AgroResQ
{
namespace Algorithms
{

class IrrigationPlanner
{
private:

    bool isDrySoil(
        const Entities::Soil& soil) const;


public:

    IrrigationPlanner();

    std::string calculatePlan(
        const Entities::Soil& soil,
        const Entities::Weather& weather) const;
};

}
}