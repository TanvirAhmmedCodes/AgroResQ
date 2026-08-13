#pragma once

#include <string>

#include "../entities/Soil.h"
#include "../entities/Weather.h"

namespace AgroResQ
{
namespace Algorithms
{

class DiseasePrediction
{
private:

    bool checkHighRisk(
        const Entities::Soil& soil,
        const Entities::Weather& weather) const;


public:

    DiseasePrediction();

    std::string predict(
        const Entities::Soil& soil,
        const Entities::Weather& weather) const;
};

}
}