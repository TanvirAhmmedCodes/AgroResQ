#pragma once

#include <string>

#include "../entities/Soil.h"
#include "../entities/Weather.h"
#include "../entities/Disaster.h"

#include "SoilHealthScore.h"
#include "DiseasePrediction.h"
#include "IrrigationPlanner.h"
#include "RecoveryPlanner.h"


namespace AgroResQ
{
namespace Algorithms
{

class DecisionSupportEngine
{

private:

    SoilHealthScore soilHealthScore;

    DiseasePrediction diseasePrediction;

    IrrigationPlanner irrigationPlanner;

    RecoveryPlanner recoveryPlanner;



public:

    DecisionSupportEngine();



    std::string generateReport(
        const Entities::Soil& soil,
        const Entities::Weather& weather);

};

}
}