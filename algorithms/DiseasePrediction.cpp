#include "DiseasePrediction.h"

namespace AgroResQ
{
namespace Algorithms
{

DiseasePrediction::DiseasePrediction() = default;



bool DiseasePrediction::checkHighRisk(
    const Entities::Soil& soil,
    const Entities::Weather& weather) const
{

    if(weather.getHumidity() > 80 &&
       soil.getMoisture() > 70)
    {
        return true;
    }


    return false;
}



std::string DiseasePrediction::predict(
    const Entities::Soil& soil,
    const Entities::Weather& weather) const
{

    if(checkHighRisk(soil, weather))
    {
        return "High Disease Risk: Fungal Infection Possible";
    }


    if(weather.getTemperature() > 35)
    {
        return "Medium Risk: Heat Related Crop Stress";
    }


    return "Low Disease Risk";
}

}
}