#pragma once

#include <string>

#include "../entities/Soil.h"
#include "../entities/Weather.h"

namespace AgroResQ
{
namespace Algorithms
{

class RecoveryPlanner
{
private:

    bool isRecoveryNeeded(
        const Entities::Soil& soil,
        const Entities::Weather& weather) const;


public:

    RecoveryPlanner();

    std::string createPlan(
        const Entities::Soil& soil,
        const Entities::Weather& weather) const;
};

}
}