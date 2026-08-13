#include "SoilHealthScore.h"

namespace AgroResQ
{
namespace Algorithms
{

SoilHealthScore::SoilHealthScore() = default;



double SoilHealthScore::calculatePhScore(
    double phLevel) const
{

    if(phLevel >= 6 &&
       phLevel <= 7.5)
    {
        return 50;
    }


    if(phLevel >= 5 &&
       phLevel <= 8.5)
    {
        return 35;
    }


    return 15;
}



double SoilHealthScore::calculateMoistureScore(
    double moisture) const
{

    if(moisture >= 40 &&
       moisture <= 70)
    {
        return 50;
    }


    if(moisture >= 20 &&
       moisture <= 80)
    {
        return 35;
    }


    return 15;
}



double SoilHealthScore::calculate(
    const Entities::Soil& soil) const
{

    double phScore =
        calculatePhScore(
            soil.getPhLevel());


    double moistureScore =
        calculateMoistureScore(
            soil.getMoisture());


    return phScore + moistureScore;
}

}
}