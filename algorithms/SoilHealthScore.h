#pragma once

#include "../entities/Soil.h"

namespace AgroResQ
{
namespace Algorithms
{

class SoilHealthScore
{
private:

    double calculatePhScore(
        double phLevel) const;

    double calculateMoistureScore(
        double moisture) const;


public:

    SoilHealthScore();

    double calculate(
        const Entities::Soil& soil) const;
};

}
}