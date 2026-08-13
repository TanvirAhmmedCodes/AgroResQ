#include "IrrigationPlanner.h"

namespace AgroResQ
{
namespace Algorithms
{

IrrigationPlanner::IrrigationPlanner() = default;



bool IrrigationPlanner::isDrySoil(
    const Entities::Soil& soil) const
{

    return soil.getMoisture() < 30;
}



std::string IrrigationPlanner::calculatePlan(
    const Entities::Soil& soil,
    const Entities::Weather& weather) const
{

    if(weather.getRainfall() > 50)
    {
        return "No Irrigation Required. Rainfall is sufficient.";
    }


    if(isDrySoil(soil))
    {
        return "High Irrigation Required. Soil moisture is low.";
    }


    if(soil.getMoisture() < 50)
    {
        return "Medium Irrigation Required.";
    }


    return "Low Irrigation Required. Soil moisture is adequate.";
}

}
}