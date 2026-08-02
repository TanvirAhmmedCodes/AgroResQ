#pragma once

#include "../entities/Disaster.h"
#include "../entities/Victim.h"

namespace AgroResQ
{
namespace Algorithms
{

class PriorityCalculator
{
private:

    double calculateDisasterScore(
        const Entities::Disaster& disaster) const;

    double calculateVictimScore(
        const Entities::Victim& victim) const;


public:

    PriorityCalculator();

    double calculateDisasterPriority(
        const Entities::Disaster& disaster) const;


    double calculateVictimPriority(
        const Entities::Victim& victim) const;
};

}
}