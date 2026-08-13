#include "RecoveryPlanner.h"

namespace AgroResQ
{
namespace Algorithms
{

RecoveryPlanner::RecoveryPlanner() = default;



bool RecoveryPlanner::isRecoveryNeeded(
    const Entities::Soil& soil,
    const Entities::Weather& weather) const
{

    if(soil.getPhLevel() < 5 ||
       soil.getPhLevel() > 8)
    {
        return true;
    }


    if(weather.getRainfall() > 100)
    {
        return true;
    }


    if(soil.getMoisture() < 20)
    {
        return true;
    }


    return false;
}



std::string RecoveryPlanner::createPlan(
    const Entities::Soil& soil,
    const Entities::Weather& weather) const
{

    if(isRecoveryNeeded(soil, weather))
    {

        if(weather.getRainfall() > 100)
        {
            return "Flood Recovery Required: Improve drainage and restore soil.";
        }


        if(soil.getPhLevel() < 5 ||
           soil.getPhLevel() > 8)
        {
            return "Soil Recovery Required: Apply soil treatment.";
        }


        return "Agriculture Recovery Required.";
    }


    return "No Major Recovery Required.";
}

}
}